#include <stdlib.h>

typedef int (*compar)(const void *, const void *);

void copy(char * first, char * second, size_t size) {
    for (int i = 0; i < size; i++) {
        *(first++) = *(second++);
    }
}

void merge(void * fp_src, size_t fp_num, void * sp_src, size_t sp_num, size_t size, compar compare) {
    char *fp_ptr = (char *)fp_src;
    char *sp_ptr = (char *)sp_src;
    
    char * tmp = (char *)malloc((fp_num + sp_num) * size);
    
    size_t i = 0, j = 0;
    
    while (i < fp_num && j < sp_num) {
        if (compare(fp_ptr, sp_ptr) < 0) {
            
            copy(tmp, fp_ptr, size);
            
            fp_ptr += size;
            tmp += size;
            
            i++;
            
        } else {
            
            copy(tmp, sp_ptr, size);
            
            sp_ptr += size;
            tmp += size;
            
            j++;
            
        }
    }
    
    while (i < fp_num) {
        
        copy(tmp, fp_ptr, size);
        
        fp_ptr += size;
        tmp += size;
        
        i++;
        
    }
    
    while (j < sp_num) {
        copy(tmp, sp_ptr, size);
        
        sp_ptr += size;
        tmp += size;
        
        j++;
    }
    
    for (i = 0; i < fp_num + sp_num; i++) {
        sp_ptr -= size;
        tmp -= size;
        copy(sp_ptr, tmp, size);
    }
    
    free(tmp);
}

void merge_sort(void * arr, size_t num, size_t size, compar compare) {
    if (num < 2) return;
    
    // fp = first part
    // sp = second part
    size_t fp_num = num / 2,
    sp_num = num - fp_num;
    
    void * fp_ptr = arr,
    * sp_ptr = (void *)((char *)arr + fp_num * size);
    
    merge_sort(fp_ptr, fp_num, size, compare);
    merge_sort(sp_ptr, sp_num, size, compare);
    
    merge(fp_ptr, fp_num, sp_ptr, sp_num, size, compare);
}