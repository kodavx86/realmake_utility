/* This is a test of the Emacs editor.
 * How do you like it?*/

class FibTest {

    public static void main(String[] args) {

	FibClass n_calc = new FibClass();
	n_calc.test("1",0,0);
	n_calc.test("2",1,1);
	n_calc.test("3",2,1);
	n_calc.test("4",14,377);
	n_calc.test("5",20,6765);
	n_calc.test("6",26,121393);

	//String resp = JOptionPane.showInputDialog("Name Here");
	//JOptionPane.showMessageDialog(null, "You said: " + resp);
	System.exit(0);
	    
    }
}

