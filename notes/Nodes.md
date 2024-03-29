# Nodes

* Each node in ROS2 should be responsible for a single, modular purpose.
* Each node can send and recieve data from other nodes via topics, services, actions and parameters.
* A single executable program can contain one or more nodes.

* Camera package may contain fllowing nodes

    * Camera driver node
    * image processing node
    * data recording node

* Reduces the code complexity
* Each node can be a different entity
* Supports different languages for different nodes.

### First Node

* required dependencies rclpy 
* create a node in python package `ros2_ws/src/my_py_pkg/my_py_pkg` create a file `my_first_node.py`

* Create file
```bash
    touch my_first_node.py
```
* Basic python node

```python
#! /usr/bin/env python3 
# above is interpretor line.


import rclpy
from rclpy.node import Node
# ti write node we import Node class


def main(args =None):
    # implement ros2 communication main code
    # starts ros2 communication
    rclpy.init(args=args)

    # new node is created
    node = Node("py_test")

    # loging data
    node.get_logger().info("Hello ROS2")

    
    rclpy.spin(node)
    # It makes our code to be alive though it is not subscribing or publishing


    # at the end shutdown
    rclpy.shutdown()

if __name__ == "__main__":
    main()

```

* Setup in an executable

    * Inform ros2 to make exetuable and specify it in entry point to the program. Update `entry_point` in the `setup.py` file

```python
            entry_points={
                'console_scripts': [
                    "py_node = my_py_pkg.my_first_node:main"
                                    ],
                        }
```
    * `py_node` is the name of the new node executable 
    * It will be installed in `ros2_ws/src/install/my_py_pkg/lib/my_py_pkg/py_node` location  

* Make it an executable
    * `chmod +x my_first_node.py`

### Run Program

* After creating node, making it executable.
* Do `colcon build` in `src` directory. 
    * Now node is ready to run

* Source the current ros2 environment by running following command from the `src` dirctory

```bash
        source ./install/setup.bash
```
    * It will source your current workspace

* Run the node 

```bash
        ros2 run my_py_pkg py_node
```
* `py_node` is the node name which we gave in `setup.py`. 

## Python Node with Oops

* Makes node more scalable

```python
import rclpy
from rclpy.node import Node

class MyCustomNode(Node): # MODIFY NAME

    def __init__(self):
        super().__init__("node_name")
        self.get_logger().info("This is Oops Node")

def main(args = None):

    rclpy.init(args=args)
    node = MyCustomNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
```

### Remapping Node

* `--ros-args` flag 
* `--rmap` or `-r` to rename

* `ros2 run my_py_pkg my_oops_node --ros-args --rmap __node:=my_oops_node1`

* Change node in run. It doesn't affect original node.


## Implementing Counter with callback timer

timer helps in publishing or subscriber nodes with a given frequency

```python

import rclpy
from rclpy.node import Node
# ti write node we import Node class

class MyNode(Node):

    def __init__(self):
        self.counter_ = 0
        super().__init__("py_test_class")
        # node name
        self.get_logger().info("Hello ROS2")
        self.create_timer(0.5 , self.timer_callback)

    # it is a callback function used to call in create_timer functiom
    def timer_callback(self):
        self.counter_ +=1
        self.get_logger().info("Hello " + str(self.counter_))

def main(args =None):
    # implement ros2 communication main code
    # starts ros2 communication
    rclpy.init(args=args)

    # new node is created
    node = MyNode()

    # loging data   
    rclpy.spin(node)
    # It makes our code to be alive though it is not subscribing or publishing
    # timer will run and you see that line printed until you exit ( Node ends )

    # at the end shutdown
    rclpy.shutdown()

if __name__ == "__main__":
    main()
```

**NOTE** : 

* It is fine to create multiple duplicate nodes.
* Keep track in the rqt and `ros2 node list`.
* If same name is used more than once it may cause unintentional errors.




## Tasks

### ros2 run

* `ros2 run <pkg_name> <executable_name>` => command `ros2 run` launches an executable from a package

* 