# Idea or Implementation Notes
## Ideas
## Implementation
##### PsyCron
- Use Static memory preallocation for allocations of PsyCron internals and Routines
  - Keep implementation hidden from non-PsyCron internals IE. User Routines
  
##### PsyRail

- Timed rails should keep a the time to be executed.
- Should keep metrics on how long it takes for TimedRoutines to execute.
  - This can be used as heuristic for the time domain scheduling.
