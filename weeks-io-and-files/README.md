# I/O, Files, and File Systems

Notes and demos.

## Byte Ordering

_If 4 bytes comprise an integer, which byte comes first?_

- Little Endian ("little end first") = lease significant byte first
- Big Endian ("big end first") = most significant byte first

## File System Ops

- create
- truncate
- delete
- read
- write

**sequential access**
- operations occur "in sequence"
- need some inherent notion of **current location** (this is typically incremented with read/write ops)
- might want an op to change the current location if we want to jump somewhere else ("seek")
- might need a notion of **record size**

vs. **direct/random access**
- operations can occur anywhere
- reads/writes need to **address** specific records
