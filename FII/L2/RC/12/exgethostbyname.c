/* - Exemplu de utilizare a primitivei gethostbyname()
    
       Autor: Lenuta Alboaie  <adria@infoiasi.ro> (c)2009
       */
        
        #include <sys/types.h>
        #include <sys/socket.h>
        #include <netinet/in.h>
        #include <errno.h>
        #include <unistd.h>
        #include <stdio.h>
        #include <string.h>
        #include <stdlib.h>
        #include <arpa/inet.h>
        #include <netdb.h>

        
        int main(int argc, char *argv[])
        {
            char **phal;
            struct hostent *hos;
            struct in_addr **addr_list;
            int i=0;
            
            if (argc !=2)
            {
               fprintf(stderr,"Numele host-ului...?\n");
               return 1;   
            }   
                                                                
            if ( (hos=gethostbyname(argv[1]))==NULL)
               {
                 perror("Eroare la gethostbyname()");
                 return 2;
              }

            printf("Numele oficial al hostului: %s\n", hos->h_name);
            printf("Aliasuri: ");
            
            for ( phal=hos->h_aliases; *phal != NULL; phal++)
              printf(" %s ",*phal); 
              printf("\n");
            if(hos->h_addrtype==AF_INET)
              {
                printf("Lungimea adresei este %d\n", hos->h_length);
              }
            
            printf("Adrese: ");
            addr_list=(struct in_addr**)hos->h_addr_list;
            for(i=0; addr_list[i]!=NULL;i++)
              {
                printf("%s ",inet_ntoa(*addr_list[i]));
              }  
            printf("\n");  
            return 0;
            
          }







         
 
          





          