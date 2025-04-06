#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void set_bit_in_byte(uint8_t *ptr, int bitpos, int value){
        uint8_t template=(uint8_t)1;
        template<<=bitpos;
        if(value) 
          *ptr=*ptr | template;
        else
          *ptr=*ptr & ( ~ template);
}
void set_bit(uint8_t *ptr, uint64_t bitpos, int value){
        uint64_t byteno;
        int bit07;
        byteno=bitpos>>3;
        bit07=(int)bitpos%8;
        set_bit_in_byte(ptr+byteno,bit07,value);
}
int get_bit_in_byte(uint8_t byte, int bitpos){
        uint8_t template=(uint8_t)1;
        template<<=bitpos;
        byte&=template;
        if(byte)
                return 1;
        else
                return 0;
}
int get_bit(uint8_t *ptr, uint64_t bitpos){
        uint64_t byteno;
        int bit07;
        byteno = bitpos>>3;    
        bit07=(int)bitpos%8;
        return get_bit_in_byte(*(ptr+byteno),bit07);
}

void print_seive(uint8_t* seive, uint64_t size, uint64_t maxnum){
    uint8_t* end = seive + size;
    uint64_t num;
    puts("2");
    for(uint8_t* i = seive; i < end; i++){
        for(int bitPos = 0; bitPos<8; bitPos++)
            if(get_bit_in_byte(*i, bitPos) == 0){
                num = ((i-seive)*8 + bitPos)*2 +3;
                if(num>maxnum){
                        free(seive);
                    putc('\n', stdout);
                    exit(EXIT_SUCCESS);
                }

                printf("%llu\n", num);
            }
    }
    putc('\n', stdout);
}

int main(int argc, char*argv[]){
        uint64_t maxnum = strtoll(argv[1], NULL, 10);
        uint64_t bytes_size =  (maxnum/16) + 1;

        uint8_t* seive = (uint8_t*)malloc(bytes_size);
        uint8_t* end = seive + bytes_size;
        memset(seive, 0, bytes_size);

        int index=0;
        uint64_t accum = 3, current = 3;

        while(current * current<=maxnum){
                current = (index<<1)+3;
                accum = current;
                while(((accum + index)>>3) < bytes_size)
                {
                        set_bit(seive,accum + index,1);
                        accum+=current;
                }
                //find next prime by skipping bits marked 1
                while(get_bit(seive,++index));

        }
        print_seive(seive, bytes_size, maxnum);
        free(seive);
        exit(EXIT_SUCCESS);
}