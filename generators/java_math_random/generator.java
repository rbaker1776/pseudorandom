import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;


public class generator
{
    public static void main(String[] args) throws IOException 
	{
		int BITSTRING_SIZE = 16000000;
        FileOutputStream out = new FileOutputStream("./randomness.txt");

        for (int i = 0; i < BITSTRING_SIZE / 4; i++) 
		{
            int num = (int)(Math.random() * Integer.MAX_VALUE);
            byte[] bytes = ByteBuffer.allocate(4).putInt(num).array();
            out.write(bytes);
        }

        out.close();
    }
}
