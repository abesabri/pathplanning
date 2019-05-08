#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/PointCloud2.h>
#include <std_msgs/Int32.h>
#include <nav_msgs/OccupancyGrid.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <string>
#include <sstream>
using namespace std;

ros::Publisher test_pub;

void test_callback(const nav_msgs::OccupancyGrid::ConstPtr &mymap) {
    
    int n,m,arr[n][m];
    cout << "Enter a grid number to print it's status" << endl;
    cin >> n,m;
    int spvalues = mymap->data[n]; //specific values, n is given by the user
    std_msgs::Int32 arr_values;
    arr_values.data = spvalues;
    test_pub.publish(arr_values);
    ROS_INFO_STREAM("Message Displayed");
    
}

int main(int argc, char *argv[]) {
    
    ROS_INFO_STREAM("STARTING NODE");
    ros::init(argc, argv, "test_node");
    
    ros::NodeHandle nh("~");
    
    test_pub = nh.advertise<std_msgs::Int32>("/map_test",10);
    ros::Subscriber test_sub = nh.subscribe("/projected_map",10,test_callback);
    
    ROS_INFO_STREAM("NODE READY");

	while(ros::ok()) {
        ros::spin();

	}
	return 0;
    
}
