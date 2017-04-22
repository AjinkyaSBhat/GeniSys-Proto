#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <Servo.h>

ros::NodeHandle  nh;
int ind,mid,ring,lil,thumb; //signals for joystick

//initiliaze movement sensitivity
int sensitivity=1;

int holdtime=15; //action delay(hold) in milliseconds

// Define and initiliaze positions
int ind_pos=0;
int mid_pos=0;
int lil_pos=0;
int ring_pos=0;
int thumb_pos=0;


//Connection ports for motor to arduino
int ind_port=9;
int mid_port=10;
int lil_port=11;
int ring_port=5;
int thumb_port=6;


Servo Servo_ind, Servo_mid, Servo_ring, Servo_lil, Servo_thumb;  // create servo object to control a servo

void messageCb( const geometry_msgs::Twist& vel_cmd){
  ind=vel_cmd.linear.x;
  mid=vel_cmd.linear.y;
  ring=vel_cmd.linear.z;
  lil=vel_cmd.angular.x;
  thumb=vel_cmd.angular.y;
  
  while (thumb!=0 || ind!=0 || mid!=0|| ring!=0|| lil!=0)
    {
    
     movetopos(ind,mid,ring,lil,thumb);
      ros::Subscriber<geometry_msgs::Twist> sub("joystick", &messageCb );
     
    }
}

ros::Subscriber<geometry_msgs::Twist> sub("joystick", &messageCb );



void setup()
{ 
  nh.initNode();
  nh.subscribe(sub);
  //Serial.begin(57600);
 Servo_ind.attach(ind_port);  // attaches the servo on pin  to the servo object
 Servo_mid.attach(mid_port);  // attaches the servo on pin  to the servo object
  Servo_ring.attach(ring_port);  // attaches the servo on pin to the servo object
  Servo_lil.attach(lil_port);  // attaches the servo on pin  to the servo object
  Servo_thumb.attach(thumb_port);  // attaches the servo on pin  to the servo object
}

void loop()
{  
  nh.spinOnce();
  delay(1);
  //moveit(vel_x,vel_y);
}

//***********************************MOVEMENT FUNCTIONS-Joystick***********************************////
void movetopos(int ind, int mid, int ring, int lil,int thumb)
{

    movthumb(thumb);
    movind(ind);
    movmid(mid);
    movring(ring);
    movlil(lil);
    ros::Subscriber<geometry_msgs::Twist> sub("joystick", &messageCb );


}

void movthumb(int thumb)
{
 if (thumb >0 )
 {
   if (thumb_pos<180)
   {
     thumb_pos=thumb_pos+sensitivity;
     Servo_thumb.write(thumb_pos);
     //ros::Subscriber<geometry_msgs::Twist> sub("joystick", &messageCb );
   }
 }
 else if (thumb <0)
 {
   if (thumb_pos>0)
   {
   thumb_pos=thumb_pos-sensitivity;
   Servo_thumb.write(thumb_pos);
   //ros::Subscriber<geometry_msgs::Twist> sub("joystick", &messageCb );
   }
 }
 else
 {
   //ros::Subscriber<geometry_msgs::Twist> sub("joystick", &messageCb );
 }
}

void movind(int ind)
{
 if (ind >0 )
 {
   if (ind_pos<180)
   {
     ind_pos=ind_pos+sensitivity;
     Servo_ind.write(ind_pos);
     //ros::Subscriber<geometry_msgs::Twist> sub("joystick", &messageCb );
   }
 }
 else if (ind <0)
 {
   if (ind_pos>0)
   {
   ind_pos=ind_pos-sensitivity;
   Servo_ind.write(ind_pos);
  // ros::Subscriber<geometry_msgs::Twist> sub("joystick", &messageCb );
   }
 }

}

void movmid(int mid)
{
 if (mid >0 )
 {
   if (mid_pos<180)
   {
     mid_pos=mid_pos+sensitivity;
     Servo_mid.write(mid_pos);
   //  ros::Subscriber<geometry_msgs::Twist> sub("joystick", &messageCb );
   }
 }
 else if (mid <0)
 {
   if (mid_pos>0)
   {
   mid_pos=mid_pos-sensitivity;
   Servo_mid.write(mid_pos);
  // ros::Subscriber<geometry_msgs::Twist> sub("joystick", &messageCb );
   }
 }
 else
 {
   //ros::Subscriber<geometry_msgs::Twist> sub("joystick", &messageCb );
 }
}

void movring(int ring)
{
 if (ring >0 )
 {
   if (ring_pos<180)
   {
     ring_pos=ring_pos+sensitivity;
     Servo_ring.write(ring_pos);
    // ros::Subscriber<geometry_msgs::Twist> sub("joystick", &messageCb );
   }
 }
 else if (ring <0)
 {
   if (ring_pos>0)
   {
   ring_pos=ring_pos-sensitivity;
   Servo_ring.write(ring_pos);
  // ros::Subscriber<geometry_msgs::Twist> sub("joystick", &messageCb );
   }
 }
 else
 {
  // ros::Subscriber<geometry_msgs::Twist> sub("joystick", &messageCb );
 }
}

void movlil(int lil)
{
 if (lil >0 )
 {
   if (lil_pos<180)
   {
     lil_pos=lil_pos+sensitivity;
     Servo_lil.write(lil_pos);
   //  ros::Subscriber<geometry_msgs::Twist> sub("joystick", &messageCb );
   }
 }
 else if (lil <0)
 {
   if (lil_pos>0)
   {
   lil_pos=lil_pos-sensitivity;
   Servo_lil.write(lil_pos);
   //ros::Subscriber<geometry_msgs::Twist> sub("joystick", &messageCb );
   }
 }
 else
 {
   //ros::Subscriber<geometry_msgs::Twist> sub("joystick", &messageCb );
 }
}
