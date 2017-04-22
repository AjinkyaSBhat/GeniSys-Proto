#!/usr/bin/env python
import rospy
import time
from geometry_msgs.msg import Twist
from std_msgs.msg import Int8
from sensor_msgs.msg import Joy

def send_Twist(data):
	move_cmd=Twist()	
#Button-Finger Mapping#
#Contract                     #Release
## A=Index ## buttons[0] - ///Down to release - axes[7] -ve//
## B=Mid ## buttons[1]-    // Right to release- axes[6] -ve//
## Y=Ring ## buttons[4]-   //Up to release- axes[7] +ve//
## X=Little ## buttons[3]- //Left to release-axes[6] +ve//
## RB=Thumb ## buttons[5]- //LB to release buttons[4]//

## RT=ALL contract ## axes[5] =1 default, -1 full press//
## LT=ALL release ## axes[2]	=1 default //
	if data.buttons[0] !=0 or  data.axes[7]<0:                 #Index
			move_cmd.linear.x=data.buttons[0]+data.axes[7]
			rospy.loginfo("Index move %d",move_cmd.linear.x)


	if data.buttons[1] !=0 or  data.axes[6]<0:                #Middle
			move_cmd.linear.y=data.buttons[1]+data.axes[6]
			rospy.loginfo("Middle move %d",move_cmd.linear.y)
			
	 	
	if data.buttons[3] !=0 or  data.axes[7]>0:                 #Ring
			move_cmd.linear.z=data.buttons[3]-data.axes[7]
			rospy.loginfo("Ring move %d",move_cmd.linear.z)
			

	if data.buttons[2] !=0 or  data.axes[6]>0:               #Little
			move_cmd.angular.x=data.buttons[2]-data.axes[6]
			rospy.loginfo("Little move %d",move_cmd.angular.x)
			

	if data.buttons[5] !=0 or  data.buttons[4]!=0:              #Thumb
			move_cmd.angular.y=data.buttons[5]-data.buttons[4]
			rospy.loginfo("Thumb move %d",move_cmd.angular.y)
	
	if data.axes[5] <0  :
		if data.axes[5] ==-1  :
			move_cmd.linear.x=1
			move_cmd.linear.y=1
			move_cmd.linear.z=1
			move_cmd.angular.x=1
			move_cmd.angular.y=1
			rospy.loginfo("All move %d",move_cmd.angular.y)
		else :
			move_cmd.linear.x=0
			move_cmd.linear.y=0
			move_cmd.linear.z=0
			move_cmd.angular.x=0
			move_cmd.angular.y=0
			rospy.loginfo("All move %d",move_cmd.angular.y)

	if data.axes[2] <0 :
		if data.axes[2] ==-1 :
			move_cmd.linear.x=-1
			move_cmd.linear.y=-1
			move_cmd.linear.z=-1
			move_cmd.angular.x=-1
			move_cmd.angular.y=-1
			rospy.loginfo("All move %d",move_cmd.angular.y)
		else :
			move_cmd.linear.x=0
			move_cmd.linear.y=0
			move_cmd.linear.z=0
			move_cmd.angular.x=0
			move_cmd.angular.y=0
			rospy.loginfo("All move %d",move_cmd.angular.y)
			
	pub.publish(move_cmd)

# Intializes everything
def start():
    
    global pub
 
    pub = rospy.Publisher('joystick', Twist, queue_size=10)
    
    # subscribed to joystick inputs on topic "joy"
    rospy.Subscriber("joy", Joy, send_Twist)
    # starts the node
    rospy.init_node('JoyStick_Conv')
    rospy.spin()

if __name__ == '__main__':
    start()
