#if !defined(_LOAD_INFO_H_)
#define _LOAD_INFO_H_

/* 
 * The structure returned here should serve to mmap the file 
 * as well as to copy the contents out so we use pages as well 
 * as raw addresses.
 * 
 * Problem arises because bss is contiguous with init data, but
 * the boundary between the two may not be a page boundary.
 * For those two, we must also use the end (to zero the part of
 * the top init data page that rightfully belongs to bss.)
 * This is not beautiful.
 */

struct load_info {
  u_long entry;       /* Entry point of executable */
  off_t t_faddr;      /* File offset of text, rounded down to page bdry */
  u_long t_vaddr;     /* Addr of text, rounded down to page bdry */
  u_long t_npg;       /* Text page count */
  u_long t_end;       /* End of text */
  off_t id_faddr;     /* File offset of init data, rounded down */
  u_long id_vaddr;    /* Addr of init data, rounded down */
  u_long id_npg;      /* Init data page count */
  u_long id_end;      /* End of init data */
  u_long ud_vaddr;    /* Addr of bss, rounded UP */
  u_long ud_npg;      /* bss page count, rounded down */
  u_long ud_end;      /* Ebnd of bss */
};


#define LI_NO_ERROR 0
#define LI_FORMAT_ERROR (-1)
#define LI_OTHER_ERROR (-2)

/*
 * LoadInfo takes the open descriptor of an executable ELF file
 * and sets the fields of the load_info structure acording to
 * the program segments in the file.
 *
 * An ELF file can contain many types of segments and sections
 * to help with linking and loading, both dynamically and statically.
 * As regards to the loading of typical executables into memory,
 * however, files have two relevant program segments:
 *    - Text segment
 *    - Data segment
 * the Data segment has a file size and a memory size.  The memory
 * size is usually larger than the file size.  The bss segment
 * (uninitialized data,) which is to created in memory even though
 * it is not present in the file, is the segment between the 
 * address that marks the end of the file-present Data
 * segment (specified by the file size of this segment) and the address
 * that marks the end of the memory-resident Data segment
 * (specified by the memory size of this segment.)  
 *
 * The fields of load_info are set to identify the three resulting
 * areas of the program as it should be loaded into memory:
 *  Text area:
 *       t_faddr:  bottom of the file "page" that contains the start
 *                 of the text segment.
 *       t_vaddr:  bottom of the memory page that will contain the start
 *                 of the text segment in memory.
 *       t_npg:    number of pages in which the text segment will reside
 *                 in memory.  Note that because of alignment this
 *                 may be one more than the size of the segment divided
 *                 by the page size.
 *       t_end:    Address immediatly above the memory-resident text 
 *                 segment will end.
 *                 (t_vaddr + (t_npg - 1) << PGESHIFT) <= 
 *                         t_end <
 *                             (t_vaddr + t_npg << PAGESHIFT)
 *
 *  The initialized data area has a siimilar set of fields for it.
 *  The bss area, however, is contiguous in memory to the init data
 *  area, and its lower region may be in a page already partially 
 *  occupied by the initialized data area.  To ease file mapping,
 *  the ud_vaddr is rounded up to the next page of where
 *  the bss region actually starts (this is the first page that
 *  is wholly occupied by uninitialized data.)  Similarly, the
 *  ud_npg field is set to the number of pages occupied by the
 *  bss area, not counting this first one if it is also partially
 *  occupied by the initialized data area.
 *  The bss area does not have a ud_faddr field because this area
 *  is not present in the file.
 * 
 *  LoadInfo returns an error code defined above:
 *     LI_NO_ERROR if everything is swell
 *     LI_FORMAT_ERROR if the file is not an ELF file, 
 *                         or is an ELF file of the wrong ELF version,
 *                         or is not a SPARC executable,
 *                         or is missing a program segment,
 *                         or etc etc
 */


extern int LoadInfo(int, struct load_info *);

#endif /* _LOAD_INFO_H_ */
