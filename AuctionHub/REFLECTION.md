#Task A: why is insertion sort the right choice here? Give a complexity argument.
- Insertion Sort is a good choice because the bids arrive in nearly sorted order, meaning each new bid is usually slightly higher than the previous one. In this situation, most elements are already in their correct positions, so Insertion Sort only needs to make a few comparisons and shifts to insert each new bid. It is also simple to implement and works in-place without requiring extra memory for another array.
- In the best case, when the data is already sorted, Insertion Sort has a time complexity of O(n). In the worst case, when the data is sorted in reverse order, it has a time complexity of O(n²). Since the bids in this scenario are nearly sorted, its performance is closer to O(n) than O(n²), making it a suitable choice for this module.

#Task C: explain when interchange sort is *acceptable* despite its O(n²) complexity.
- Interchange Sort is acceptable when the dataset is small, such as a batch of fewer than 50 bids. Although it has O(n²) time complexity, the number of comparisons is still manageable for a small dataset. It is also easy to implement, requires only O(1) extra space, and allows us to count the number of swaps. Therefore, for small batches, its simplicity and low memory usage make it a reasonable choice, while for larger datasets, a more efficient sorting algorithm would be preferable.

#1. real-world justification for each algorithm.
- Insertion Sort (Live Auction Monitor): Insertion sort is useful when the data is small or already almost sorted because its best-case complexity is O(n). It is simple to implement and can insert a new bid into its correct position without having to sort the entire list again.
- Selection Sort (Top-K Bid Finder): Selection sort fits this module because it repeatedly selects the highest bid from the remaining records. It sorts in-place and requires only O(1) extra space, making it suitable for finding the highest bids without using additional memory for another list.
- Interchange Sort (Price Anomaly Validator): Interchange sort is useful here because its logic is simple and easy to implement. It is also easy to count swap operations, making it suitable for analyzing small data batches and tracking how many swaps are needed to sort them.
- Bubble Sort with Early Stop (Stabilization Detector): Bubble sort with an early-stop condition is useful for checking whether a list is already sorted because it can stop after a pass with no swaps. Therefore, it can detect an already sorted data set quickly without performing unnecessary passes.
- Quick Sort (Full Historical Sorter): Quick sort is a good choice for sorting a large number of records, such as 100,000 bids, because its average-case complexity is O(n log n). Using the median-of-three pivot also helps avoid some poor pivot choices in practice and can improve its performance on large datasets.

#2. Quick Sort runtime on 100k records.
- The measured runtime was 185 miliseconds.

#3. One bug I encountered.
- One bug I encountered was in my comparisons function. I accidentally wrote a.amount < a.amount instead of comparing a.amount with b.amount. This expression was always false, so the comparison function did not correctly order bids by amount. I diagnosed the problem by reviewing the comparison logic and checking which two values it was supposed to compare. After correcting it to a.amount < b.amount, the sorting logic could compare two different bids properly.

#4. Three prompts sent to the LLM and their ratings.
[Green] "Generate C++ code using std::mt19937 to produce 100,000 random Bid structs and write them to a file."
[Green] "Explain how the median-of-three pivot selection works so I can understand it."
[Yellow] "Help me write the reflection for this sorting assignment, including the runtime, the bug I encountered, and the complexity of Quick Sort."

#5. Quick Sort worst-case complexity with median-of-three pivot
- Quick Sort with a median-of-three pivot still has a worst-case time complexity of O(n²). Median-of-three chooses the median value among the first, middle, and last elements, which often gives a better pivot and more balanced partitions. However, it does not guarantee balanced partitions for every input. If the partitions repeatedly become very uneven, Quick Sort can still perform O(n²) operations in the worst case.