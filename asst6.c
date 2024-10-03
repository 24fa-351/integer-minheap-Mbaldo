#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "some_heap.h"  // Assuming some_heap.h contains the heap function declarations

/*
Assignment 5: Integer minheap
*/

// Function to generate a random number between min and max (inclusive)
unsigned long long rand_between(unsigned long long min, unsigned long long max) {
    if (min == max) return min;  // Handle edge case where min == max
    unsigned long long range = max - min + 1;
    return min + (rand() % range);
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "some_heap.h"  // Assuming some_heap.h contains the heap function declarations

// Function to test heap functionality and write output to a file
void test_heap(void) {
    FILE *output_file = fopen("heap_output.txt", "w");  // Open a file to write the output
    if (!output_file) {
        fprintf(stderr, "Failed to open file for writing\n");
        exit(1);
    }

    heap_t *heap = heap_create(200);  // Create a heap with a capacity of 200
    if (!heap) {
        fprintf(stderr, "Failed to create heap\n");
        exit(1);
    }

    // Insert 20 random keys into the heap
    for (heap_key_t ix = 0; ix < 20; ix++) {
        heap_key_t key = rand_between(0, 1000);  // Generate random key between 0 and 1000
        heap_insert(heap, key, (heap_value_t){.as_int = key});  // Insert key as both key and value
        heap_print(heap, output_file);  // Print the heap after each insertion to file
    }

    // Remove the minimum key 10 times from the heap
    for (int ix = 0; ix < 10; ix++) {
        heap_value_t min_val = heap_remove_min(heap);  // Remove the minimum value
        heap_key_t key = min_val.as_int;  // Access the integer value from the union
        fprintf(output_file, "Removed %llu\n", key);  // Write the removed key to the file
        heap_print(heap, output_file);  // Print the heap after each removal to file
    }

    heap_free(heap);  // Free the heap after use
    fclose(output_file);  // Close the file
}


// Main function
int main(int argc, char *argv[]) {
    (void)argc;  // Mark argc as unused
    (void)argv;  // Mark argv as unused

    srand(time(NULL));  // Seed the random number generator with the current time

    test_heap();  // Call the heap test function
    return 0;  // Return success
}
