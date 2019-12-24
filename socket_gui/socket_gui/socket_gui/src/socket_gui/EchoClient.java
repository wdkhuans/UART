package socket_gui;
import java.net.*;
import java.text.SimpleDateFormat;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.*;
import java.util.*;

import javax.swing.JLabel;
import javax.swing.JTextField;
public class EchoClient {
  private String host="192.168.43.236";
  //private String host="192.168.205.25";
  private int port=8266;
  //private int port=8000;
  private Socket socket;
  static int n=0;
  static int m=0;
  static String msg;
  static String time;
  static String rec;
  static String str;
  static String weather;
  static String humiture;
  public EchoClient()throws IOException
 {
     socket=new Socket(host,port);  
 }
  public static void main(String args[])throws IOException
  {
	  Calendar c = Calendar.getInstance();//���Զ�ÿ��ʱ���򵥶��޸�
	  
	    Frame f = new Frame("���ƽ���");
	    f.setSize(1000,1000);
	    
		f.setLocation(900, 300);
		Button button1 = new Button("����");
		Button button2 = new Button("�ص�");
		Button button3 = new Button("��Ϣ��ǽ");
		Button button4 = new Button("��ʾ��Ϣ");
		Button button7 = new Button("������ʪ��");
	
		JTextField name = new JTextField(30);
		JTextField text_tq = new JTextField(30);
		JTextField showtext = new JTextField(30);
		JTextField text_time = new JTextField(30);
		JTextField text_sd = new JTextField(30);
		
		JLabel nameLab = new JLabel("������ʾ��Ϣ��");
		JLabel nameLab3 = new JLabel("�¶ȣ�");
		JLabel nameLab2 = new JLabel("��Ƭ�����ص���Ϣ��");
		JLabel nameLab4 = new JLabel("�˿�ʱ�䣺");
		JLabel nameLab5 = new JLabel("ʪ�ȣ�");
		
		GridBagLayout gridBagLayout =new GridBagLayout(); //ʵ�������ֶ���
		GridBagConstraints gridBagConstraints=new GridBagConstraints();//ʵ�����������������������й���
        gridBagConstraints.fill=GridBagConstraints.BOTH;//�÷�����Ϊ���������������ڵ�������������Ҫ��ʱ����ʾ��� 
        //NONE�������������С�� 
        //HORIZONTAL���ӿ������ʹ����ˮƽ��������������ʾ���򣬵��ǲ��ı�߶ȡ� 
        //VERTICAL���Ӹ������ʹ���ڴ�ֱ��������������ʾ���򣬵��ǲ��ı��ȡ� 
        //BOTH��ʹ�����ȫ��������ʾ����

        button1.setBackground(Color.red);
        button1.setForeground(Color.white);
        button2.setBackground(Color.blue);
        button2.setForeground(Color.white);
		f.setLayout(gridBagLayout);
		
		
		gridBagConstraints.gridx=0;
        gridBagConstraints.gridy=0;
        gridBagConstraints.gridwidth=5;                                             
        gridBagConstraints.gridheight=5;            
        gridBagLayout.setConstraints(button1, gridBagConstraints);  //����
        
        gridBagConstraints.gridx=30;
        gridBagConstraints.gridy=0;
        gridBagConstraints.gridwidth=5;                                             
        gridBagConstraints.gridheight=5;            
        gridBagLayout.setConstraints(button2, gridBagConstraints);  //�ص�
        
        gridBagConstraints.gridx=0;
        gridBagConstraints.gridy=20;
        gridBagConstraints.gridwidth=5;                                             
        gridBagConstraints.gridheight=5;            
        gridBagLayout.setConstraints(button3, gridBagConstraints);  //��Ϣ��ǽ
        
        
        gridBagConstraints.gridx=0;
        gridBagConstraints.gridy=60;
        gridBagConstraints.gridwidth=5;                                             
        gridBagConstraints.gridheight=5;            
        gridBagLayout.setConstraints(button4, gridBagConstraints);  //��ʾʱ��
        
   
        gridBagConstraints.gridx=30;
        gridBagConstraints.gridy=60;
        gridBagConstraints.gridwidth=5;                                             
        gridBagConstraints.gridheight=5;            
        gridBagLayout.setConstraints(button7, gridBagConstraints);  //��ʪ��

    
        
        
        
        
        gridBagConstraints.gridx=30;
        gridBagConstraints.gridy=100;
        gridBagConstraints.gridwidth=50;                                             
        gridBagConstraints.gridheight=5;            
        gridBagLayout.setConstraints(name, gridBagConstraints);  //�����
        gridBagConstraints.gridx=0;
        gridBagConstraints.gridy=100;
        gridBagConstraints.gridwidth=30;                                             
        gridBagConstraints.gridheight=5;            
        gridBagLayout.setConstraints(nameLab, gridBagConstraints); //�������ʾ
        gridBagConstraints.gridx=85;
        gridBagConstraints.gridy=100;
        gridBagConstraints.gridwidth=5;                                             
        gridBagConstraints.gridheight=5;            
        gridBagLayout.setConstraints(button3, gridBagConstraints);  //��Ϣ��ǽ��ť
        
        gridBagConstraints.gridx=30;
        gridBagConstraints.gridy=120;
        gridBagConstraints.gridwidth=100;                                             
        gridBagConstraints.gridheight=5;            
        gridBagLayout.setConstraints(text_tq, gridBagConstraints); //��ʪ�������
        gridBagConstraints.gridx=0;
        gridBagConstraints.gridy=120;
        gridBagConstraints.gridwidth=30;                                             
        gridBagConstraints.gridheight=5;            
        gridBagLayout.setConstraints(nameLab3, gridBagConstraints); //��ʪ�������
        
        gridBagConstraints.gridx=0;
        gridBagConstraints.gridy=140;
        gridBagConstraints.gridwidth=30;                                             
        gridBagConstraints.gridheight=5;            
        gridBagLayout.setConstraints(nameLab5, gridBagConstraints); //ʪ��ʾ�������ʾ
        gridBagConstraints.gridx=30;
        gridBagConstraints.gridy=140;
        gridBagConstraints.gridwidth=100;                                             
        gridBagConstraints.gridheight=5;            
        gridBagLayout.setConstraints(text_sd, gridBagConstraints);   //ʪ��

        gridBagConstraints.gridx=0;
        gridBagConstraints.gridy=160;
        gridBagConstraints.gridwidth=30;                                             
        gridBagConstraints.gridheight=5;            
        gridBagLayout.setConstraints(nameLab4, gridBagConstraints); //�����ʾ�������ʾ
        gridBagConstraints.gridx=30;
        gridBagConstraints.gridy=160;
        gridBagConstraints.gridwidth=100;                                             
        gridBagConstraints.gridheight=5;            
        gridBagLayout.setConstraints(text_time, gridBagConstraints);   //ʱ�䷵�ص���Ϣ��ʾ����
        
        gridBagConstraints.gridx=0;
        gridBagConstraints.gridy=180;
        gridBagConstraints.gridwidth=30;                                             
        gridBagConstraints.gridheight=5;            
        gridBagLayout.setConstraints(nameLab2, gridBagConstraints); //�����ʾ�������ʾ
        gridBagConstraints.gridx=30;
        gridBagConstraints.gridy=180;
        gridBagConstraints.gridwidth=100;                                             
        gridBagConstraints.gridheight=5;            
        gridBagLayout.setConstraints(showtext, gridBagConstraints);   //��Ƭ�����ص���Ϣ��ʾ����
        

		
		f.add(button1);
		f.add(showtext);
		f.add(text_tq);
		f.add(text_time);
		f.add(button2);
		f.add(name);
		f.add(nameLab);
		f.add(nameLab2);
		f.add(nameLab3);
		f.add(nameLab4);
		f.add(nameLab5);
		f.add(button3);
		f.add(button4);

		f.add(button7);
		f.add(text_sd);
		
		
		f.setSize(300, 200);
		f.setVisible(true);
		f.addWindowListener(new MyWindowListener());
		
		button1.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
		         {
				  
				   msg="light";
			       System.out.println("lighting");
			       try {
					new EchoClient().talk();
				 } catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				 }
			       showtext.setText(rec);
	             }
		});
		button2.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
		         {
				
				   msg="close";
			       System.out.println("closing light");
			       try {
					new EchoClient().talk();
				 } catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				 }
			       showtext.setText(rec);
	             }
		});
		button3.addActionListener(new ActionListener()//��Ϣ��ǽ
		{
			public void actionPerformed(ActionEvent e)
		         {
				
				   msg=name.getText();
			       System.out.println("get the message");
			       try {
					new EchoClient().talk();
				 } catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				 }
			       showtext.setText(rec);
	             }
		});
		button4.addActionListener(new ActionListener()//��ʾ��Ϣ
		{
			public void actionPerformed(ActionEvent e)
		         {
				   Date now = new Date(); 
				   SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");//���Է�����޸����ڸ�ʽ
				   time = dateFormat.format( now ); 
				   text_time.setText(time);
				   msg="mmm";
			       System.out.println("show information");
			       try {
					new EchoClient().talk();
				 } catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				 }
			       
			       showtext.setText(rec);
	             }
		});
		
		 
		button7.addActionListener(new ActionListener()//������ʪ��
		{
			public void actionPerformed(ActionEvent e)
		         {
		
				
						 msg="iii";
						 try {
								new EchoClient().talk();
							 } catch (IOException e1) {
								// TODO Auto-generated catch block
								e1.printStackTrace();
							 }
						 text_tq.setText(rec);
						 showtext.setText(rec);
						 showtext.paintImmediately(showtext.getBounds()); 
						 msg="vvv";
						 try {
								new EchoClient().talk();
							} catch (IOException e1) {
								// TODO Auto-generated catch block
								e1.printStackTrace();
							}
						 text_sd.setText(rec);
						 showtext.setText(rec);		
	             }
		});
	

  }
  private PrintWriter getWriter(Socket socket)throws IOException{
    OutputStream socketOut = socket.getOutputStream();
    return new PrintWriter(socketOut,true);
  }
  private BufferedReader getReader(Socket socket)throws IOException{
    InputStream socketIn = socket.getInputStream();
    return new BufferedReader(new InputStreamReader(socketIn));
  }
  public void talk()throws IOException {
    try{
      BufferedReader br=getReader(socket);
      PrintWriter pw=getWriter(socket);
      //BufferedReader localReader=new BufferedReader(new InputStreamReader(System.in));
      //String msg=null;
     // while((msg=localReader.readLine())!=null){
   
        pw.println(msg);
        //System.out.println(br.readLine());
        System.out.println("successfuly sending message");
        rec=String.valueOf(br.readLine());
 	    System.out.println(rec);
 	    //rec=str;
 	    
        //System.out.println(br);

    }catch(IOException e){
       e.printStackTrace();
    }finally{
       try{socket.close();}catch(IOException e){e.printStackTrace();}
    }
  }
  

  
}
/*
class MyWindowListener extends WindowAdapter{
	public void windowClosing(WindowEvent e){
		Window window = (Window) e.getComponent();
		window.dispose();
	}
}*/

/****************************************************
 * ���ߣ�������                                     *
 * ��Դ��<<Java�����̾���>>                       *
 * ����֧����ַ��www.javathinker.org                *
 ***************************************************/
