/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package sorttest;

import java.util.Arrays;
import java.util.Random;

/**
 * @author Rex
 */
public class SortTest {
  private int[] anNumbers;
  private long lElapseTime;
  private long lOriginalCheckSum;
  private volatile boolean bRunning;

  /**The  call to sort() will likely be spawned through a thread, so this provides a mechanism to terminate intractable sort algorithms. */
  public void killSort() { bRunning = false; }

  /** All algorithms and their details are expressed here as enumerated types; each has a virtual sort() method. */
  public enum SortTypeMethod {
    BUBBLE_SORT("Bubble Sort") {
      public long sort(SortTest st) {
        long lStartTime = System.currentTimeMillis();

        for (int i = 0; st.bRunning  &&  i < st.anNumbers.length; ++i) {
          for (int j = 0; j < i; j++) {
            if (st.anNumbers[i] < st.anNumbers[j]) {
              int temp = st.anNumbers[i]; //swap
              st.anNumbers[i] = st.anNumbers[j];
              st.anNumbers[j] = temp;
            } // end comparison if
          } // end inner for loop
        } // end outer for loop
        return System.currentTimeMillis() - lStartTime;
      }
    },
    SELECTION_SORT("Selection Sort") {
      public long sort(SortTest st) {
        // Algorithm 
        long lStartTime = System.currentTimeMillis();

        int nLastIndexToSort = st.anNumbers.length - 1;
        for (int nCurrentPositionToFill = 0; st.bRunning  &&  nCurrentPositionToFill < nLastIndexToSort; nCurrentPositionToFill++) {
          // inner loop searches for the next smallest item in the remaining unsorted data set
          int nIndexToSmallest = nCurrentPositionToFill;
          for (int j = nIndexToSmallest + 1; j < st.anNumbers.length; j++) {
            if (st.anNumbers[j] < st.anNumbers[nIndexToSmallest]) {
              nIndexToSmallest = j;
            }
          } // end inner loop
          // Now have index to smallest on this pass, swap it to
          int nTemp = st.anNumbers[nIndexToSmallest];
          st.anNumbers[nIndexToSmallest] = st.anNumbers[nCurrentPositionToFill];
          st.anNumbers[nCurrentPositionToFill] = nTemp;
        } // end outer loop
        return System.currentTimeMillis() - lStartTime;
      }
    },
    INSERTION_SORT("Insertion Sort") {
      public long sort(SortTest st) {
        long lStartTime = System.currentTimeMillis();

        for (int nNextToInsertIndex = 1; st.bRunning  &&  nNextToInsertIndex < st.anNumbers.length; ++nNextToInsertIndex) {
          int nNextToInsertValue = st.anNumbers[nNextToInsertIndex];
          int nScan = nNextToInsertIndex - 1;
          while (nScan >= 0 && st.anNumbers[nScan] > nNextToInsertValue) {
            st.anNumbers[nScan + 1] = st.anNumbers[nScan];
            --nScan;
          }
          st.anNumbers[nScan + 1] = nNextToInsertValue;
          //DisplayComparisons();
        }
        return System.currentTimeMillis() - lStartTime;
      }
    },
    MERGE_SORT("Merge Sort (Iterative)") {
      public long sort(SortTest st) {
        long lStartTime = System.currentTimeMillis();

        int nNumToSort = st.anNumbers.length;
        int[] anTempMergeSortNumbers = new int[nNumToSort];
        for (int nSizeOfOneMergeSet = 1; st.bRunning  &&  nSizeOfOneMergeSet < nNumToSort; nSizeOfOneMergeSet = nSizeOfOneMergeSet * 2) {
          for (int nLeft = 0, nRight = nSizeOfOneMergeSet; nLeft < nNumToSort; nLeft += nSizeOfOneMergeSet * 2, nRight += nSizeOfOneMergeSet * 2) {
            if (nRight >= nNumToSort) { // Only Left subset
              MergeSilentNoCopyBack(st.anNumbers, anTempMergeSortNumbers, nLeft, nNumToSort - 1, nNumToSort - 1);
            } else {
              int nEndOfRight = nRight + nSizeOfOneMergeSet - 1;
              if (nEndOfRight >= nNumToSort) {
                nEndOfRight = nNumToSort - 1;
              }
              MergeSilentNoCopyBack(st.anNumbers, anTempMergeSortNumbers, nLeft, nRight - 1, nEndOfRight);
            }
          }
          // No need to copy values back from temp array . . . merely swap the roles of the two arrays
          int[] anExchangeTemp = anTempMergeSortNumbers;
          anTempMergeSortNumbers = st.anNumbers;
          st.anNumbers = anExchangeTemp;
        }

        anTempMergeSortNumbers = null; // and pray for garbage collector to release . . .
        return System.currentTimeMillis() - lStartTime;
      }
      private void MergeSilentNoCopyBack(int[] anNumbers, int[] anTempNumbers, int nLeft, int nEndLeft, int nEndRight) {
        int nIndexToSorted = nLeft;
        int nRight = nEndLeft + 1;
        // LOOP 1: Copy values selectively from left or right depending on which is smaller
        while (nLeft <= nEndLeft && nRight <= nEndRight) {
          if (anNumbers[nLeft] < anNumbers[nRight]) {
            anTempNumbers[nIndexToSorted++] = anNumbers[nLeft++];
          } else {
            anTempNumbers[nIndexToSorted++] = anNumbers[nRight++];
          }
        }
        // LOOP 2: Copy remaining values from left-side
        while (nLeft <= nEndLeft) {
          anTempNumbers[nIndexToSorted++] = anNumbers[nLeft++];
        }
        // LOOP 3: Copy remaining values from right-side
        while (nRight <= nEndRight) {
          anTempNumbers[nIndexToSorted++] = anNumbers[nRight++];
        }
      }
    },
    NATIVE_JAVA_SORT("Native Java Sort") {
      public long sort(SortTest st) {
        long lStartTime = System.currentTimeMillis();
        Arrays.sort(st.anNumbers);
        return System.currentTimeMillis() - lStartTime;
      }
    };

    private final String sName;

    SortTypeMethod(String sName) { this.sName = sName; }
    public abstract long sort(SortTest st);

    @Override
    public String toString() { return sName; }
  } // end enum SortTypeMethod

  public SortTest(int nSize, boolean bFixedRandomSeed) throws InstantiationException, OutOfMemoryError {
    if (nSize <= 0) {
      throw new InstantiationException();
    }
    lOriginalCheckSum = 0L;
    anNumbers = new int[nSize]; // could generate OutOfMemoryError which will be treated as a handled exception rather than an error
    bRunning = true;
    Random randGenerator = (bFixedRandomSeed ? new Random(1L) : new Random()); // Debug mode with fixed seed
    for (int i = 0; i < anNumbers.length; ++i) {
      if (! bRunning)
        throw new InstantiationException();
      anNumbers[i] = randGenerator.nextInt(nSize);
      lOriginalCheckSum += anNumbers[i];
    }
    bRunning = false;
  } // end SortTest() constructor

  public boolean isSorted() {
    long lCurrentCheckSum = anNumbers[0];

    for (int i = 1; i < anNumbers.length; ++i) {
      if (anNumbers[i - 1] > anNumbers[i]) {
        return false;
      }
      lCurrentCheckSum += anNumbers[i];
    }
    return lOriginalCheckSum == lCurrentCheckSum;
  }

/**
 * expected to be spawned from an independent thread where other threads may terminate this thread through bRunning
 * @param stm SortTypeMethod is used to establish binding to the virtual method implementation in the enum set of algorithms
 * @return long value representing elapse time in milliseconds
 */
  public long sort(SortTypeMethod stm) {
    bRunning = true;
    return stm.sort(this);
  }

  public long getElapseTime() {
    return lElapseTime;
  }

  @Override
  public String toString() {
    final int nMAX_DISPLAY_SET = 100;
    int nSizeOfDisplaySet = anNumbers.length / 2;
    if (nSizeOfDisplaySet > nMAX_DISPLAY_SET) {
      nSizeOfDisplaySet = nMAX_DISPLAY_SET;
    }
    StringBuilder sbResult = new StringBuilder(String.format("<br><br><b>First %d:</b> %d", nSizeOfDisplaySet, anNumbers[0]));
    for (int i = 1; i < nSizeOfDisplaySet; ++i) {
      sbResult.append(", ");
      sbResult.append(anNumbers[i]);
    }
    int nStartOfLastSet = anNumbers.length - nSizeOfDisplaySet;
    sbResult.append(String.format("<br><b>Last %d</b>: %d", nSizeOfDisplaySet, anNumbers[nStartOfLastSet]));
    for (int i = nStartOfLastSet + 1; i < anNumbers.length; ++i) {
      sbResult.append(", ");
      sbResult.append(anNumbers[i]);
    }
    return sbResult.toString();
  } // end toString()
} // end class SortTest
