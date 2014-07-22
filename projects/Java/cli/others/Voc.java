import java.io.*;

public class Voc {
	static String vowels = "aAeEiIoOuU";
	static int process(String word)
	{
		int cnt = 0;
		boolean tmp;
		for (int i = 0; i < word.length(); ++i) {
			tmp = false;
			for (int j = 0; j < vowels.length(); ++j) {
				if (word.charAt(i) == vowels.charAt(j)) {
					tmp = true;
					break;
				}
			}
			if (tmp) {
				++cnt;
			}
		}
		return cnt;
	}
	public static void main(String[] args) throws IOException
	{
		BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
		System.out.println("Input: ");
		String word = input.readLine();
		System.out.println(process(word));
	}
}
