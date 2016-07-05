class TestRef
{
    static void FillArray(ref int[] arr)
    {
        // Do nothing if arr is null.
        if (arr == null)
        {
            return;
        }
	// Fill Array with counters.
	for(int i = 0; i < arr.Length; i++) {
		arr[i] = i;	
	}
    }

    static void Main()
    {
        // Initialize the array:
        int[] theArray = new int[8];

        // Pass the array using ref:
        FillArray(ref theArray);

        // Display the array:
        System.Console.WriteLine("Array elements are:");
	foreach(int n in theArray) {
            System.Console.Write(n + " ");
	}

        // Keep the console window open in debug mode.
        System.Console.WriteLine("Press any key to exit.");
        System.Console.ReadKey();
    }
}
