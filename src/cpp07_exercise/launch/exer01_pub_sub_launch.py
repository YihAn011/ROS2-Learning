from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess,RegisterEventHandler
from launch.event_handlers import OnProcessExit

def generate_launch_description():
    #start 2 turtle nodes
    t1 = Node(package="turtlesim",executable="turtlesim_node")
    t2 = Node(package="turtlesim",executable="turtlesim_node", namespace="t2")
    #make seconde turtle turn 180
    rotate = ExecuteProcess(
        cmd=["ros2 action send_goal /t2/turtle1/rotate_absolute turtlesim/action/RotateAbsolute \"{'theta': 3.14}\""],#3.14=180
        output="both",
        shell=True
    )
    #call customized node(must execute after seconde node finished)
    exer01 = Node(package="cpp07_exercise",executable="exer01_pub_sub")
    #register event
    register_rotate_exit_event=RegisterEventHandler(
        event_handler=OnProcessExit(#trigger action
            target_action=rotate,#target node
            on_exit=exer01#trigger event
        )
    )
    return LaunchDescription([t1,t2,rotate,register_rotate_exit_event])