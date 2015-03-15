#include <stdio.h>

int main(int argc, char *const *argv)
{
   printf("One-time pad cryptor.\n");

   if ( argc == 4 )
   {
      FILE *input  = fopen(argv[1], "rb");
      FILE *output = fopen(argv[2], "wb");
      if ( input != NULL && output != NULL )
      {
         unsigned char buffer[BUFSIZ];
         size_t count, i, j = 0;
         do {
            count = fread(buffer, sizeof *buffer, sizeof buffer, input);
            for ( i = 0; i < count; ++i )
            {
               buffer[i] ^= argv[3][j++];
               if ( argv[3][j] == '\0' )
               {
                  j = 0; /* restart at the beginning of the key */
               }
            }
            fwrite(buffer, sizeof *buffer, count, output);
         } while ( count == sizeof buffer );
         fclose(input);
         fclose(output);
      }

   }
   else printf("Usage: %s file_to_crypt crypted_file key\n",argv[0]);
   return 0;
}
