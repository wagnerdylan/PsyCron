# PsyCron

PsyCron is a simplistic priority and time based cooperative scheduler designed for embedded applications. 

## Concepts

> All system resources have a lifetime which equals the life of the entire of the program. This means, once created and/or added to the system, resources cannot be removed.

This is done to ensure the system memory footprint stays exactly the same. This alleviates some of the concern of developing software for devices with very limited memory.

> All Resource allocation and initialization within the PsyCron system is done before the execution of any routine.

This is done due to the constraint placed by the concept listed above.

> Routines, once called run till completion.

Done because PsyCron does not support routine/task preemption.

> TODO Add more

## Operation

### PsyCron Specific

### Routines

#### Priority Routines

Priority routines are designed to execute as fast as possible. The operating frequency of the priority routine is determined by the execution environment. This means priority routine operating frequency is relative to other routines in the same execution environment. *Note:* Priority routines assigned a priority value of 0 will execute exactly next. A priority value of 0 should be used for routines which need to be executed exactly next and are only active for one cycle.

```
template <typename EnvType>
class PriorityExample : public psycron::PriorityRoutine<EnvType>
{
public:
  
  // Optional method 
  void init();
  
private:

  // Required method
  void run();
  
};
```

#### Timed Routines

TODO

```
template <typename EnvType>
class TimedExample : public psycron::TimedRoutine<EnvType>
{
public:
  
  // Optional method 
  void init();
  
private:

  // Required method
  void run();
  
};
```

#### Active / Non-Active Routine States

TODO

### Tracks

A track in PsyCron is an application. Tracks hold the necessary utility to facilitate the handling of routines within PsyCron. A Track also provides a way to store a mutable environment which can be accessed by all routines executing in under it. 

```
TODO add track creation example
```
