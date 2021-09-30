#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <jansson.h>



#define BUF_LEN 4096
#define h_addr h_addr_list[0]
#define PORT 80
#define MAX_CHARS (1024 * 8)
#define DEFAULT_SIZE 512
#define COMM_MAX         5

int isexist =0;
int j;
int length;
int docnum = 3;
char* s;
char querykey[50];
int querynum;

typedef struct Document_t {
        char        id                  [DEFAULT_SIZE]  ;
        char        place_name          [DEFAULT_SIZE]  ;
        char        category_group_code [DEFAULT_SIZE]  ;
        char        category_group_name [DEFAULT_SIZE]  ;
        char        category_name       [DEFAULT_SIZE]  ;
        char        phone               [DEFAULT_SIZE]  ;
        char        address_name        [DEFAULT_SIZE]  ;
        char        road_address_name   [DEFAULT_SIZE]  ;
        char        x                   [DEFAULT_SIZE]  ;
        char        y                   [DEFAULT_SIZE]  ;
        char        place_url           [DEFAULT_SIZE]  ;
        char        distance            [DEFAULT_SIZE]  ;
} Document ;


Document list[3];

typedef struct Region_t {
        char        region              [DEFAULT_SIZE]  ;
} Region ;

typedef struct SameName_t {
        Region      regions             [COMM_MAX]              ;
        char        keyword             [DEFAULT_SIZE]  ;
        char        selected_region     [DEFAULT_SIZE]  ;
} SameName ;

typedef struct Meta_t {
        int         total_count                                                 ;
        int         pageable_count                                              ;
        short       is_end                                                              ;
        SameName    same_name                                                   ;
} Meta ;

typedef struct DataSet_t {
        Document    documents           [COMM_MAX]                                      ;
        int                     objectnum                                                       ;
} DataSet ;




void print_json(json_t *root);
void print_json_aux(json_t *element, int indent);
void print_json_indent(int indent);
const char *json_plural(size_t count);
void print_json_object(json_t *element, int indent);
void print_json_array(json_t *element, int indent);
void print_json_string(json_t *element, int indent);
void print_json_integer(json_t *element, int indent);
void print_json_real(json_t *element, int indent);
void print_json_true(json_t *element, int indent);
void print_json_false(json_t *element, int indent);
void print_json_null(json_t *element, int indent);
void decoding(const char *key, json_t *value,int indent,int listnum);



void print_json_id(json_t *element, int indent,int num);
void print_json_place_name(json_t *element, int indent,int num);
void print_json_group_code(json_t *element, int indent,int num);
void print_json_group_name(json_t *element, int indent,int num) ;
void print_json_category_name(json_t *element, int indent,int num) ;
void print_json_phone(json_t *element, int indent,int num) ;
void print_json_address_name(json_t *element, int indent,int num);
void print_json_road_addr(json_t *element, int indent,int num);
void print_json_x(json_t *element, int indent,int num) ;
void print_json_y(json_t *element, int indent,int num);
void print_json_place_url(json_t *element, int indent,int num);
void print_json_distance(json_t *element, int indent,int num);






void print_json(json_t *root) { print_json_aux(root, 0); }

void print_json_aux(json_t *element, int indent) {

        switch (json_typeof(element)) {
                case JSON_OBJECT:
                        print_json_object(element, indent);
                        break;
                case JSON_ARRAY:
                        print_json_array(element, indent);
                        break;
                case JSON_STRING:
                        print_json_string(element, indent);
                        break;
                case JSON_INTEGER:
                        print_json_integer(element, indent);
                        break;
                case JSON_REAL:
                        print_json_real(element, indent);
                        break;
                case JSON_TRUE:
                        print_json_true(element, indent);
                        break;
                case JSON_FALSE:
                        print_json_false(element, indent);
                        break;
                case JSON_NULL:
                        print_json_null(element, indent);
                        break;
                default:
                        fprintf(stderr, "unrecognized JSON type %d\n", json_typeof(element));
        }
}


void print_json_indent(int indent) {
        int i;
        for (i = 0; i < indent; i++) {
                putchar(' ');
        }
}

const char *json_plural(size_t count) { return count == 1 ? "" : "s"; }

int listnum = 0;

void print_json_object(json_t *element, int indent) {
        size_t size;
        const char *key;
        json_t *value;

        print_json_indent(indent);
        size = json_object_size(element);

        printf("JSON Object of %d pair%s:\n", (long long)size, json_plural(size));
        json_object_foreach(element, key, value) {
                print_json_indent(indent + 2);
                printf("JSON Key: \"%s\"\n", key);
                decoding(key,value,indent,listnum);
                print_json_aux(value, indent + 2);
        }
        listnum++;
}

void decoding(const char *key, json_t *value,int indent,int listnum){

        if(strcmp(key,"id")== 0){
                print_json_id(value,indent + 2,listnum);
        }

        if(strcmp(key,"place_name")== 0){
                print_json_place_name(value,indent + 2,listnum);
        }

        if(strcmp(key,"category_group_code")== 0){
                print_json_group_code(value,indent + 2,listnum);
        }

        if(strcmp(key,"category_group_name")== 0){
                print_json_group_name(value,indent + 2,listnum);
        }

        if(strcmp(key,"category_name")== 0){
                print_json_category_name(value,indent + 2,listnum);
        }

        if(strcmp(key,"phone")== 0){
                print_json_phone(value,indent + 2,listnum);
        }

        if(strcmp(key,"address_name")== 0){
                print_json_address_name(value,indent + 2,listnum);
        }

        if(strcmp(key,"road_address_name")== 0){
                print_json_road_addr(value,indent + 2,listnum);
        }

        if(strcmp(key,"x")== 0){
                print_json_x(value,indent + 2,listnum);
        }

        if(strcmp(key,"y")== 0){
                print_json_y(value,indent + 2,listnum);
        }

        if(strcmp(key,"place_url")== 0){
                print_json_place_url(value,indent + 2,listnum);
        }

        if(strcmp(key,"distance")== 0){
                print_json_distance(value,indent + 2,listnum);
        }


}

void print_json_id(json_t *element, int indent,int num) {
        print_json_indent(indent);

        strcpy(list[num].id,json_string_value(element));
        printf("JSON String test: \"%s\"\n", json_string_value(element));
}

void print_json_place_name(json_t *element, int indent,int num) {
        print_json_indent(indent);

        strcpy(list[num].place_name,json_string_value(element));
        printf("JSON String test: \"%s\"\n", json_string_value(element));
}


void print_json_group_code(json_t *element, int indent,int num) {
        print_json_indent(indent);

        strcpy(list[num].category_group_code,json_string_value(element));
        printf("JSON String test: \"%s\"\n", json_string_value(element));
}


void print_json_group_name(json_t *element, int indent,int num) {
        print_json_indent(indent);
        strcpy(list[num].category_group_name,json_string_value(element));
        printf("JSON String test: \"%s\"\n", json_string_value(element));
}

void print_json_category_name(json_t *element, int indent,int num) {
        print_json_indent(indent);
        strcpy(list[num].category_name,json_string_value(element));
        printf("JSON String test: \"%s\"\n", json_string_value(element));
}

void print_json_phone(json_t *element, int indent,int num) {
        print_json_indent(indent);
        strcpy(list[num].phone,json_string_value(element));
        printf("JSON String test: \"%s\"\n", json_string_value(element));
}


void print_json_address_name(json_t *element, int indent,int num) {
        print_json_indent(indent);
        strcpy(list[num].address_name,json_string_value(element));
        printf("JSON String test: \"%s\"\n", json_string_value(element));
}


void print_json_road_addr(json_t *element, int indent,int num) {
        print_json_indent(indent);
        strcpy(list[num].road_address_name,json_string_value(element));
        printf("JSON String test: \"%s\"\n", json_string_value(element));
}


void print_json_x(json_t *element, int indent,int num) {
        print_json_indent(indent);
        strcpy(list[num].x,json_string_value(element));
        printf("JSON String test: \"%s\"\n", json_string_value(element));
}


void print_json_y(json_t *element, int indent,int num) {
        print_json_indent(indent);
        strcpy(list[num].y,json_string_value(element));
        printf("JSON String test: \"%s\"\n", json_string_value(element));
}


void print_json_place_url(json_t *element, int indent,int num) {
        print_json_indent(indent);
        strcpy(list[num].place_url,json_string_value(element));
        printf("JSON String test: \"%s\"\n", json_string_value(element));
}

void print_json_distance(json_t *element, int indent,int num) {
        print_json_indent(indent);
        strcpy(list[num].distance,json_string_value(element));
        printf("JSON String test: \"%s\"\n", json_string_value(element));
}



void print_json_array(json_t *element, int indent) {
        size_t i;
        size_t size = json_array_size(element);
        print_json_indent(indent);

        printf("JSON Array of %lld element%s:\n", (long long)size, json_plural(size));
        docnum = (long long)size;
        for (i = 0; i < size; i++) {
                print_json_aux(json_array_get(element, i), indent + 2);
        }
}

void print_json_string(json_t *element, int indent) {
        print_json_indent(indent);
        printf("JSON String: \"%s\"\n", json_string_value(element));
}

void print_json_integer(json_t *element, int indent) {
        print_json_indent(indent);
        printf("JSON Integer: \"%" JSON_INTEGER_FORMAT "\"\n", json_integer_value(element));
}

void print_json_real(json_t *element, int indent) {
        print_json_indent(indent);
        printf("JSON Real: %f\n", json_real_value(element));
}

void print_json_true(json_t *element, int indent) {
        (void)element;
        print_json_indent(indent);
        printf("JSON True\n");
}

void print_json_false(json_t *element, int indent) {
        (void)element;
        print_json_indent(indent);
        printf("JSON False\n");
}

void print_json_null(json_t *element, int indent) {
        (void)element;
        print_json_indent(indent);
        printf("JSON Null\n");
}


json_t *load_json(const char *text) {
        json_t *root;
        json_error_t error;

        root = json_loads(text, 0, &error);

        if (root) {
                return root;
        } else {
                fprintf(stderr, "json error on line %d: %s\n", error.line, error.text);
                return (json_t *)0;
        }
}

char str[4096];
char *temp;
json_t *root;
json_error_t error;
char ptr[4096];

int main(int argc,char *argv[]){

        int s,n,len_in,len_out,wn;
        struct sockaddr_in server_addr;
        char *haddr;
        char buf[BUF_LEN+1];
        int port=80;
        struct hostent *he;

        if ( argc < 4 )
        {
                fprintf( stderr, "파라매터 값이 입력되지 않았습니다.\n <url> <keyword> <API key>  \n ex) ./decode dapi.kakao.com eluon f981f957a2262e02fdb05cee92cc99b5\n" );
                return 1;
        }


        he = gethostbyname(argv[1]);



        if(!he){
                printf("gethostname failed\n");
                return -1;
        }
        if((s=socket(PF_INET,SOCK_STREAM,0))<0){
                printf("can not create socket\n");
                return -1;
        }
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family=AF_INET;
        server_addr.sin_addr =*((struct in_addr *)he->h_addr);

        server_addr.sin_port=htons(port);

        if(connect(s,(struct sockaddr *) &server_addr,sizeof(server_addr)) ==-1 ) {
                printf("fail\n");
                close(s);
                return -1;
        }

        sprintf(buf, "GET https://dapi.kakao.com/v2/local/search/keyword.json?query=%s HTTP/1.0\r\nAuthorization: KakaoAK %s \r\n\r\n",argv[2],argv[3]);
        printf("%s\n",buf);
        if((wn= write(s,buf,strlen(buf)))<0) return -1;


        memset(buf,0,sizeof(buf));


        while((n=read(s,buf,BUF_LEN))>0){
        //      printf("%s",buf);

                char* temp = strstr(buf,"{");
                if(temp){
                        isexist=1;
                }
                if(isexist==1){
                        strcat(str,buf);
                }


        }


        char *temp = strstr(str,"{");
        printf("\n\n\n\n\n\n\n\n\n\n");
        printf("================  JSON DATA  ====================\n");

        printf("%s\n", temp);         //자른 문자 출력
        printf("\n\n\n\n\n\n\n\n\n\n");

        length = strlen(str);



        root = json_loads( temp, 0, &error );
        if ( !root )
        {
                fprintf( stderr, "error: on line %d: %s\n", error.line, error.text );
                return 1;
        }

        const char *key;
        json_t *value;

        void *iter = json_object_iter( root );
        while( iter )
        {
                key = json_object_iter_key(iter);
                value = json_object_iter_value(iter);


                iter = json_object_get(root, "keyname");
        }

        print_json(root);


        printf("\n알고싶은 key 정보를 입력하세요 \n");
        scanf("%s",&querykey);

        int i;
        if(strcmp(querykey,"x")==0){
                for(i=0;i<3;i++){
                        printf("value값: %s\n",list[i].x);
                }
        }

        json_decref(root);

        memset(buf,0,sizeof(buf));
        memset(str,0,sizeof(str));
        close(s);
}
