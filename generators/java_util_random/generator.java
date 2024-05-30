import java.io.FileOutputStream;
import java.nio.ByteBuffer;
import java.util.Random;
import java.io.IOException;


public class generator
{
    public static void main(String[] args) throws IOException
	{
		int BITSTRING_SIZE = 16000000;
		FileOutputStream out = new FileOutputStream("randomness.txt");
		Random rand = new Random();

		for (int i = 0; i < BITSTRING_SIZE / 4; i++)
		{            
			int num = rand.nextInt();
			byte[] bytes = ByteBuffer.allocate(4).putInt(num).array();
			out.write(bytes);
		}

		out.close();
    }
}
