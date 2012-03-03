
public class SplitTest {
	public static void main(String[] args) {
		String sParagraph = "This is a paragraph (with several sentences "
				+ ". . . and lots of punctuation). It's clear that parsing "
				+ "can be complex! You might need to shout, \"Help!\"";
		System.out.println(sParagraph);
		String[] asCollectionOfWords = sParagraph.split("[^a-zA-Z_0-9']+");
		for (String s : asCollectionOfWords)
			System.out.println(s);
	} // end main()
} // end class SplitTest
