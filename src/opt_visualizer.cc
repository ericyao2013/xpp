/**
 @file    optimization_visualizer.cc
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    May 31, 2016
 @brief   Brief description
 */

#include <xpp/opt_visualizer.h>
#include <xpp/marker_array_builder.h>

#include <xpp/ros/ros_helpers.h>
#include <xpp/ros/topic_names.h>

namespace xpp {

using MarkerArrayMsg = visualization_msgs::MarkerArray;

OptVisualizer::OptVisualizer ()
{
  ::ros::NodeHandle n;

  traj_sub_      = n.subscribe(xpp_msgs::robot_trajectory_cart, 1,
                               &OptVisualizer::TrajectoryCallback, this);

  contacts_sub_  = n.subscribe(xpp_msgs::contact_vector, 1,
                               &OptVisualizer::ContactsCallback, this);

  rviz_pub_      = n.advertise<MarkerArrayMsg>(xpp_msgs::rviz_optimized, 1);
}

OptVisualizer::~OptVisualizer ()
{
}

void
OptVisualizer::TrajectoryCallback (const TrajMsg::ConstPtr& traj_msg)
{
  ROS_INFO_STREAM("Received new robot trajectory");
  MarkerArrayBuilder msg_builder;
  msg_builder.robot_traj_ = ros::RosHelpers::RosToXppCart(*traj_msg);


  MarkerArrayMsg msg;
  auto first_state = ros::RosHelpers::RosToXpp(traj_msg->states.at(0));
  msg_builder.VisualizeState(first_state, msg);

//  msg_builder.AddStart(msg);
//  msg_builder.AddBodyTrajectory(msg);
//  msg_builder.AddZmpTrajectory(msg);
//  msg_builder.AddFootholds(msg);
//  msg_builder.AddSupportPolygons(msg);
//  msg_builder.AddStartStance(msg);


  rviz_pub_.publish(msg);
}

void
OptVisualizer::ContactsCallback (const ContactVecMsg& contact_msg)
{
  auto contacts = ros::RosHelpers::RosToXpp(contact_msg);
  MarkerArrayMsg msg;

  // already publishing using trajectory callback
//  msg_builder_.AddFootholds(msg, contacts, "footholds", visualization_msgs::Marker::SPHERE, 1.0);
//  ros_publisher_optimized_.publish(msg);
}

} /* namespace xpp */
