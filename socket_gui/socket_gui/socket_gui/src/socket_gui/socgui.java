package socket_gui;

import java.awt.*;
import java.awt.event.*;
import java.util.Scanner;

import javax.swing.*;
public class socgui {
	static String a;
	static int n=0;
	public static void main(String args[]) {
		Scanner cin=new Scanner(System.in);
		
		
		Frame f = new Frame("Flow Layout");
		f.setLocation(500, 500);
		Button button1 = new Button("¿ªµÆ");
		Button button2 = new Button("¹ØµÆ");
		
		f.setLayout(new FlowLayout());
		f.add(button1);
		f.add(button2);

		f.setSize(300, 200);
		f.setVisible(true);
		f.addWindowListener(new MyWindowListener());
		
		button1.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
		         {
				   n=n+1;
			       System.out.println("kkk");
			       System.out.println(a);
			       
	             }
		});
		button2.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
		         {
			       System.out.println("ggg");
			      	             }
		});

	}
}
class MyWindowListener extends WindowAdapter{
	public void windowClosing(WindowEvent e){
		Window window = (Window) e.getComponent();
		window.dispose();
	}
}
