void motor_arm(int thrust)
{
   left.writeMicroseconds(thrust);
   right.writeMicroseconds(thrust);
   front.writeMicroseconds(thrust);
   back.writeMicroseconds(thrust);
}
