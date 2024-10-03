#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include "some_heap.h"

#define KEY_NOT_PRESENT -1

// Helper functions for parent, left child, and right child
unsigned int heap_parent(unsigned int index) {
    return (index - 1) / 2;
}

unsigned int heap_left_child(unsigned int index) {
    return 2 * index + 1;
}

unsigned int heap_right_child(unsigned int index) {
    return 2 * index + 2;
}

unsigned int heap_level(unsigned int index) {
    return (unsigned int) log2(index + 1);  // Use log2 safely
}

unsigned int heap_size(heap_t *heap) {
    return heap->size;
}


// Create a heap with a given capacity
heap_t *heap_create(int capacity) {
    heap_t *heap = (heap_t *)malloc(sizeof(heap_t));
    if (!heap) {
        return NULL;
    }
    heap->size = 0;
    heap->capacity = capacity;
    heap->data = (heap_node_t *)malloc(capacity * sizeof(heap_node_t));
    if (!heap->data) {
        free(heap);
        return NULL;
    }
    return heap;
}

// Free the memory allocated for the heap
void heap_free(heap_t *heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

// Swap two elements in the heap
void heap_swap(heap_t *heap, unsigned int index1, unsigned int index2) {
    heap_node_t temp = heap->data[index1];
    heap->data[index1] = heap->data[index2];
    heap->data[index2] = temp;
}

// Bubble up to maintain the heap property after insertion
void heap_bubble_up(heap_t *heap, unsigned int index) {
    while (index > 0 && heap->data[index].key < heap->data[heap_parent(index)].key) {
        heap_swap(heap, index, heap_parent(index));
        index = heap_parent(index);
    }
}

// Bubble down to maintain the heap property after removal
void heap_bubble_down(heap_t *heap, unsigned int index) {
    unsigned int left = heap_left_child(index);
    unsigned int right = heap_right_child(index);
    unsigned int smallest = index;

    if (left < heap_size(heap) && heap->data[left].key < heap->data[smallest].key) {
        smallest = left;
    }

    if (right < heap_size(heap) && heap->data[right].key < heap->data[smallest].key) {
        smallest = right;
    }

    if (smallest != index) {
        heap_swap(heap, index, smallest);
        heap_bubble_down(heap, smallest);
    }
}

void heap_print(heap_t *heap, FILE *fp) {
    for (unsigned int ix = 0; ix < heap_size(heap); ix++) {
        fprintf(fp, "%3u - %3u : " HEAP_KEY_FORMAT "\n", heap_level(ix), ix,
               heap->data[ix].key);
    }
    fprintf(fp, "\n");
}

// Insert into the heap
void heap_insert(heap_t *heap, heap_key_t key, heap_value_t data) {
    if (heap_size(heap) == heap->capacity) {
        return;
    }

    heap->data[heap_size(heap)].key = key;
    heap->data[heap_size(heap)].value = data;
    heap->size++;

    heap_bubble_up(heap, heap_size(heap) - 1);
}

// Remove the minimum element from the heap
heap_value_t heap_remove_min(heap_t *heap) {
    if (heap_size(heap) == 0) {
        return (heap_value_t){.as_int = KEY_NOT_PRESENT};
    }

    heap_value_t min = heap->data[0].value;

    heap->size--;

    // Move the last element to the root
    heap->data[0] = heap->data[heap_size(heap)];

    // Bubble it down to the correct position
    heap_bubble_down(heap, 0);

    return min;
}
