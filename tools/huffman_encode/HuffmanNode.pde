import java.util.LinkedList;

/** Node of a Huffman tree, used for Huffman encoder.
  * All node-related recursive functions are implemented here.
  * This is used to represent both leaf nodes and non-leaf nodes.
  * Non-leaf nodes can have any number of children - just assign an
  * appropriately-sized array into children.
  */
class HuffmanNode implements Comparable {
  public double weight;
  public int c; // color (only for leaf nodes)
  public HuffmanNode[] children; // only for non-leaf nodes

  HuffmanNode (double in_weight, int in_c) {
    weight = in_weight; 
    c = in_c;
    children = null;
  }

  boolean equals(Object o) {
    if (getClass() != o.getClass()) {
      return false;
    }
    HuffmanNode other = (HuffmanNode)o;
    return weight == other.weight;
  }

  int compareTo(Object o) {
    HuffmanNode other = (HuffmanNode)o;
    if (weight < other.weight) {
      return -1;
    } else if (weight == other.weight) {
      return 0;
    } else {
      return 1;
    }
  }

  /** Get maximum depth of nodes below this one. */
  int getMaxDepth() {
    if (children == null) {
      // leaf node
      return 0;
    } else {
      // non-leaf node
      int max_child_depth = 0;
      for (int i = 0; i < children.length; i++) {
        max_child_depth = max(max_child_depth, children[i].getMaxDepth());
      }
      return max_child_depth + 1;
    }
  }

  /** Get average codewords per pixel. */
  double getWeightedPathLength(int depth) {
    if (children == null) {
      // leaf node
      return weight * depth;
    } else {
      // non-leaf node
      double sum = 0.0;
      for (int i = 0; i < children.length; i++) {
        sum += children[i].getWeightedPathLength(depth + 1);
      }
      return sum;
    }
  }

  /** Write codeword sequences for each color into lookup table. */
  void enumerateCodes(ArrayList<LinkedList<Integer>> lut, LinkedList<Integer> prefix) {
    if (children == null) {
      // leaf node
      lut.set(c, prefix);
    } else {
      // non-leaf node
      for (int i = 0; i < children.length; i++) {
        LinkedList<Integer> copy = new LinkedList<Integer>(prefix);
        copy.add(i);
        children[i].enumerateCodes(lut, copy);
      }
    }
  }

  /** Dump pre-order traversal of Huffman tree into an array. */
  void dumpTree(ArrayList<Integer> out) {
    ArrayList<Integer> tree_details = new ArrayList<Integer>();
    int[] child_index = new int[children.length];
    for (int i = 0; i < children.length; i++) {
      if (children[i].children == null) {
        // child is a leaf node
        out.add(children[i].c | 0x80000000); // set leaf node bit
      } else {
        // child is a non-leaf node
        // This should be the index where the child's tree is stored, but we don't
        // that yet, so just output a placeholder
        child_index[i] = out.size(); // mark index to update later
        out.add(0); // do not set leaf node bit
      }
    }
    // Update child tree indices
    for (int i = 0; i < children.length; i++) {
      if (children[i].children != null) {
        out.set(child_index[i], out.size());
        children[i].dumpTree(out);
      }
    }
  }

}

