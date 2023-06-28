#! /usr/bin/env python3 
# above is interpretor line.


import rclpy
from rclpy.node import Node
# ti write node we import Node class


def main(args =None):
    # implement ros2 communication main code
    rclpy.init(args=args)


    node = Node("py_test")
    node.get_logger().info("Hello ROS2")
    rclpy.spin(node)
    # It makes our code to be alive though it is not subscribing or publishing

    rclpy.shutdown()

if __name__ == "__main__":
    main()