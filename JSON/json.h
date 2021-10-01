
void print_json_id(json_t *element, int indent,int num);
void print_json_place_name(json_t *element, int indent,int num);
void print_json_group_code(json_t *element, int indent,int num);
void print_json_group_name(json_t *element, int indent,int num) ;
void print_json_phone(json_t *element, int indent,int num) ;
void print_json_address_name(json_t *element, int indent,int num);
void print_json_road_addr(json_t *element, int indent,int num);
void print_json_x(json_t *element, int indent,int num) ;
void print_json_y(json_t *element, int indent,int num);
void print_json_place_url(json_t *element, int indent,int num);
void print_json_distance(json_t *element, int indent,int num);
void print_json_category_name(json_t *element, int indent,int num);

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




