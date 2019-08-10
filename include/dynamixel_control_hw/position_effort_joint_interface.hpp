#ifndef dynamixel_position_effort_joint_interface
#define dynamixel_position_effort_joint_interface

#include <hardware_interface/hardware_interface.h>  // for HardwareInterfaceException
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/internal/hardware_resource_manager.h>

namespace dynamixel
{
// joint handle having 2 commands
class JointHandle2Commands : public hardware_interface::JointHandle
{
public:
  JointHandle2Commands() : hardware_interface::JointHandle(), cmd2_(NULL)
  {
  }

  JointHandle2Commands(const hardware_interface::JointStateHandle& js, double* cmd, double* cmd2)
    : hardware_interface::JointHandle(js, cmd), cmd2_(cmd2)
  {
    if (!cmd2_)
    {
      throw hardware_interface::HardwareInterfaceException("Cannot create handle '" + js.getName() +
                                                           "'. 2nd command data pointer is null.");
    }
  }

  JointHandle2Commands(const hardware_interface::JointHandle& j, double* cmd2)
    : hardware_interface::JointHandle(j), cmd2_(cmd2)
  {
    if (!cmd2_)
    {
      throw hardware_interface::HardwareInterfaceException("Cannot create handle '" + j.getName() +
                                                           "'. 2nd command data pointer is null.");
    }
  }

  void setCommand2(double command2)
  {
    assert(cmd2_);
    *cmd2_ = command2;
  }

  double getCommand2() const
  {
    assert(cmd2_);
    return *cmd2_;
  }

private:
  double* cmd2_;
};

class PositionEffortJointInterface
  : public hardware_interface::HardwareResourceManager<JointHandle2Commands, hardware_interface::ClaimResources>
{
};

}  // namespace dynamixel

#endif