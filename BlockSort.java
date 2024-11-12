package io.github.arrayv.sorts.merge;

import io.github.arrayv.main.ArrayVisualizer;
import io.github.arrayv.sorts.templates.Sort;
import io.github.arrayv.utils.Delays;
import io.github.arrayv.utils.Highlights;
import io.github.arrayv.utils.Reads;
import io.github.arrayv.utils.Writes;

public final class BlockSort extends Sort {
    private Delays delays;
    private Highlights highlights;
    private Reads reads;
    private Writes writes;

    public BlockSort(ArrayVisualizer arrayVisualizer) {
        super(arrayVisualizer);
        this.delays = arrayVisualizer.getDelays();
        this.highlights = arrayVisualizer.getHighlights();
        this.reads = arrayVisualizer.getReads();
        this.writes = arrayVisualizer.getWrites();

        this.setSortListName("Block Sort");
        this.setRunAllSortsName("Block Sort");
        this.setRunSortName("Block Sort");
        this.setCategory("Hybrid Sorts");
        this.setBucketSort(false);
        this.setRadixSort(false);
        this.setUnreasonablySlow(false);
        this.setUnreasonableLimit(0);
        this.setBogoSort(false);
    }

    @Override
    public void runSort(int[] array, int length, int bucketCount) {
        int blockSize = 4; // Örneğin 4 elemanlık bloklar
        for (int i = 0; i <= length - 1; i += blockSize) {
            insertionSort(array, i, Math.min(i + blockSize - 1, length - 1));
        }
        for (int size = blockSize; size < length; size *= 2) {
            for (int i = 0; i <= length - size - 1; i += 2 * size) {
                mergeInPlace(array, i, i + size - 1, Math.min(i + 2 * size - 1, length - 1));
            }
        }
    }

    private void insertionSort(int[] array, int left, int right) {
        for (int i = left + 1; i <= right; i++) {
            int key = array[i];
            int j = i - 1;
            while (j >= left && reads.compareValues(array[j], key) > 0) {
                writes.write(array, j + 1, array[j], 0.01, true, false);
                highlights.markArray(1, j);
                delays.sleep(0.1);
                j--;
            }
            writes.write(array, j + 1, key, 0.1, true, false);
        }
    }

    private void mergeInPlace(int[] array, int left, int mid, int right) {
        int i = left, j = mid + 1;
        while (i <= mid && j <= right) {
            if (reads.compareValues(array[i], array[j]) <= 0) {
                i++;
            } else {
                int temp = array[j];
                for (int k = j; k > i; k--) {
                    writes.write(array, k, array[k - 1], 0.01, true, false);
                    highlights.markArray(2, k);
                    delays.sleep(0.1);
                }
                writes.write(array, i, temp, 0.1, true, false);
                i++;
                mid++;
                j++;
            }
            highlights.markArray(3, i);
            delays.sleep(0.1);
        }
    }
}
