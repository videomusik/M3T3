import controlP5.*;
import processing.serial.*;

static char NEW = '!';
static char OK = '*';
static char PRINT = '&';

ForceProfilePlot fpp;
Button send;
Button print;

//Serial port
Serial p; 

void setup() {
   
  int b = 15;
  //int h = (displayHeight / 3);    (work in certain resolution)
  //int w = displayWidth / 2;       (work in certain resolution)
  int w = 720; 
  int h = 300;    
  
  println("w: " + w + " h: " + h);
 
  fpp = new ForceProfilePlot("Force Profile - Perception Terrain", w, h, b, b, 80, true);
  
  ControlP5 cp5 = new ControlP5(this);
  
  send = cp5.addButton("send");
  send.setPosition(w - 20, 2*h + 2*b + 7);
  send.setSize(35, 15);
  send.setColorForeground(color(127,34,255));
  send.setColorBackground(color(50,50,50));
        
  size(w + 60, 2*h + 60);
  
  p = new Serial(this, Serial.list()[5], 9600);

  println("serial");
  for(int i = 0; i < Serial.list().length; i++) {
    println(Serial.list()[i]);
  }
  
}

void draw() {
  background(0);
  fpp.draw();
  
  if(p.available() > 0) {
    String in = p.readStringUntil('\n');
    if(in != null) {
      println(in);
      String[] t = splitTokens(in);
      fpp.cursor_at_ctrl_point(Integer.parseInt(t[1]) / (800 / fpp.forces.length));
    }
  }
  
}

void mouseDragged() {
  fpp.drag(mouseX, mouseY);
}

void mouseClicked() 
{
  fpp.click(mouseX, mouseY);
}

void mouseReleased() {
  fpp.release();
}

public void send() {
  
  send.setOff();
  
  int s = 800 / fpp.forces.length;
  float dx = 1023.0f / (fpp.forces.length - 1);
  float ddx = dx / s;
  for(int i = 0; i < fpp.forces.length-1; i++) {
    float k = fpp.forces[i];
    float m = (fpp.forces[i+1] - k) / dx;  
    for(int j = 0; j < s; j++) {
      int d = (int)(k + m*j);
      serial_send(d);
    }
  }          
  send.setOn();  
}

public boolean serial_send(int i) {    
  char msb = (char) (i / 256);
  char lsb = (char) (i & 0xff);
  p.write(lsb);
  p.write(msb);
  return true;
}

