/* This is a test of the Emacs editor.
 * How do you like it?*/

public class FibClass {

    public long calc_fib(int n) {
	
	long total,prev;
	total = prev = 1;

	if (n == 0)
	    return 0;
	else if ( n == 1)
	    return 1;

	for(;n > 2; total += prev, prev = total - prev, n--);

	return total;
    }

    public void test (String tnum, int num,int fib) {
	
	System.out.print("TEST " + tnum + ": ");
	if(calc_fib(num) == fib)
	    System.out.println("PASS");
	else {
	    System.out.print("FAIL");
	    System.out.print(" | NUM: " + num + " EV: " + fib);
	    System.out.println(" GOT: " + calc_fib(num));
	}
    }
}

