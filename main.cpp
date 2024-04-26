// Participantes: 
// Sebastian Ramirez C.I:31567908
// Angel Vivas       C.I:30890743

#include "defs.h"

void swap_int(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void print_array(int arr[], size_t len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
        printf("\n");
    }
}

void swap_cliente(cliente_t *cliente1, cliente_t *cliente2) {
    cliente_t tmp = *cliente1;
    *cliente1 = *cliente2;
    *cliente2 = tmp;
}

void swap_productos(producto_t *producto1, producto_t *producto2) {
    producto_t tmp = *producto1;
    *producto1 = *producto2;
    *producto2 = tmp;
}

void vec_quick_sort(vector<int> *vec, int start, int end) {
    if (end <= start) {
        return;
    }

    int pivot = vec->at(end);
    int i = start-1;

    for (int j = start; j <= end; j++) {
        if (vec->at(j) < pivot) {
            i++;
            swap(vec->at(j), vec->at(i));
        }
    }
    i++;
    swap(vec->at(end), vec->at(i));

    vec_quick_sort(vec, start, i-1);
    vec_quick_sort(vec, i+1, end);
}

void vec_productos_quick_sort(vector<producto_t> *productos, int start, int end) {
    if (end <= start) {
        return;
    }

    char *pivot = productos->at(end).descripcion;
    int i = start-1;

    for (int j = start; j <= end; j++) {
        if (strcasecmp(productos->at(j).descripcion, pivot) < 0) {
            i++;
            swap(productos->at(j), productos->at(i));
        }
    }
    i++;
    swap(productos->at(end), productos->at(i));

    vec_productos_quick_sort(productos, start, i-1);
    vec_productos_quick_sort(productos, i+1, end);
}

void vec_productos_merge(vector<producto_t> *left_vec, vector<producto_t> *right_vec, vector<producto_t> *vec) {
    int left_len = vec->size()/2;
    int right_len = vec->size() - left_len;
    int i = 0;
    int l = 0;
    int r = 0;

    while (l < left_len && r < right_len) {
        if (tolower(left_vec->at(l).descripcion[0]) < tolower(right_vec->at(r).descripcion[0])) {
            vec->at(i) = left_vec->at(l);
            i++;
            l++;
        } else {
            vec->at(i) = right_vec->at(r);
            i++;
            r++;
        }
    }
    while (l < left_len) {
        vec->at(i) = left_vec->at(l);
        i++;
        l++;
    }
    while (r < right_len) {
        vec->at(i) = right_vec->at(r);
        i++;
        r++;
    }
}

void vec_productos_merge_sort(vector<producto_t> *vec) {
    int len = vec->size();
    if (len <= 1) {
        return;
    }

    int mid = len/2;
    vector<producto_t> left_vec; 
    vector<producto_t> right_vec; 
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (i < mid) {
            left_vec.push_back(vec->at(i));
        } else {
            right_vec.push_back(vec->at(i));
            j++;
        }
    }
    vec_productos_merge_sort(&left_vec);
    vec_productos_merge_sort(&right_vec);
    vec_productos_merge(&left_vec, &right_vec, vec);
}

void vec_clientes_merge(vector<cliente_t> *left_vec, vector<cliente_t> *right_vec, vector<cliente_t> *vec) {
    int left_len = vec->size()/2;
    int right_len = vec->size() - left_len;
    int i = 0;
    int l = 0;
    int r = 0;

    while (l < left_len && r < right_len) {
        int cnt = 0;
        while (true) {
            char c1 = tolower(left_vec->at(l).nombre[cnt]); 
            char c2 = tolower(right_vec->at(r).nombre[cnt]); 
            if (c1 == c2) {
                cnt++;
                continue;
            }
            if (c1 < c2) {
                vec->at(i) = left_vec->at(l);
                i++;
                l++;
            } else {
                vec->at(i) = right_vec->at(r);
                i++;
                r++;
            }
            break;
        }
    }
    while (l < left_len) {
        vec->at(i) = left_vec->at(l);
        i++;
        l++;
    }
    while (r < right_len) {
        vec->at(i) = right_vec->at(r);
        i++;
        r++;
    }
}

void vec_clientes_merge_sort(vector<cliente_t> *vec) {
    int len = vec->size();
    if (len <= 1) {
        return;
    }

    int mid = len/2;
    vector<cliente_t> left_vec; 
    vector<cliente_t> right_vec; 
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (i < mid) {
            left_vec.push_back(vec->at(i));
        } else {
            right_vec.push_back(vec->at(i));
            j++;
        }
    }
    vec_clientes_merge_sort(&left_vec);
    vec_clientes_merge_sort(&right_vec);
    vec_clientes_merge(&left_vec, &right_vec, vec);
}

void vec_merge(vector<int> *left_vec, vector<int> *right_vec, vector<int> *vec) {
    int left_len = vec->size()/2;
    int right_len = vec->size() - left_len;
    int i = 0;
    int l = 0;
    int r = 0;

    while (l < left_len && r < right_len) {
        if (left_vec->at(l) < right_vec->at(r)) {
            vec->at(i) = left_vec->at(l);
            i++;
            l++;
        } else {
            vec->at(i) = right_vec->at(r);
            i++;
            r++;
        }
    }
    while (l < left_len) {
        vec->at(i) = left_vec->at(l);
        i++;
        l++;
    }
    while (r < right_len) {
        vec->at(i) = right_vec->at(r);
        i++;
        r++;
    }

}

void vec_merge_sort(vector<int> *vec) {
    int len = vec->size();
    if (len <= 1) {
        return;
    }

    int mid = len/2;
    vector<int> left_vec; 
    vector<int> right_vec; 
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (i < mid) {
            left_vec.push_back(vec->at(i));
        } else {
            right_vec.push_back(vec->at(i));
            j++;
        }
    }
    vec_merge_sort(&left_vec);
    vec_merge_sort(&right_vec);
    vec_merge(&left_vec, &right_vec, vec);
}

void swap(void *a, void *b) {
    char tmp = *((char*)a);
    *((char*)a) = *((char*)b); 
    *((char*)b) = tmp; 
}

bool check_str_int(const char* str) {
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        if (*str < 48 || *str > 57) {
            return false;
        } else {
            str++;
        }
    }
    return true;
}

void bubble_sort(int arr[], size_t arr_len) {
    for (int i = 0; i < arr_len; i++) {
        for (int j = 0; j < arr_len-i; j++) {
            if (arr[j] < arr[j-1]) {
                swap_int(&arr[j], &arr[j-1]);
            }
        }
    }
}

void productos_bubble_sort(vector<producto_t> *productos) {
    for (int i = 0; i < productos->size(); i++) {
        for (int j = 1; j < productos->size()-i; j++) {
            if (tolower(productos->at(j).descripcion[0]) < tolower(productos->at(j-1).descripcion[0])) {
                swap(productos->at(j), productos->at(j-1));
            }
        }
    }
}

void swap_binario_cliente(fstream& clientes1, int pos1, fstream& clientes2, int pos2) {
    int clientes1_curr_pos = clientes1.tellp()/sizeof(cliente_t);
    int clientes2_curr_pos = clientes1.tellp()/sizeof(cliente_t);
    cliente_t tmp_cliente1 = {0};
    cliente_t tmp_cliente2 = {0};

    clientes1.seekp(pos1 * sizeof(cliente_t));
    clientes1.seekg(pos1 * sizeof(cliente_t));
    clientes2.seekp(pos2 * sizeof(cliente_t));
    clientes2.seekg(pos2 * sizeof(cliente_t));

    clientes1.read((char*)&tmp_cliente1, sizeof(cliente_t));
    clientes2.read((char*)&tmp_cliente2, sizeof(cliente_t));

    clientes1.write((char*)&tmp_cliente2, sizeof(cliente_t));
    clientes2.write((char*)&tmp_cliente1, sizeof(cliente_t));

    clientes1.clear();
    clientes2.clear();
    clientes1.seekg(0, ios::beg);
    clientes1.seekp(0, ios::beg);
    clientes2.seekg(0, ios::beg);
    clientes2.seekp(0, ios::beg);
}

void set_binario_clientes(fstream& clientes1, int pos1, fstream& clientes2, int pos2) {
    cliente_t tmp_cliente = {0};

    clientes2.seekg(pos2 * sizeof(cliente_t));
    clientes2.read((char*)&tmp_cliente, sizeof(cliente_t));

    clientes1.seekp(pos1 * sizeof(cliente_t));
    clientes1.write((char*)&tmp_cliente, sizeof(cliente_t));
}

int obtener_tamano_binario_clientes(fstream& binario_clientes) {
    binario_clientes.seekg(0, ios::end);
    int result = (int)binario_clientes.tellg()/sizeof(cliente_t);
    binario_clientes.clear();
    binario_clientes.seekg(0, ios::beg);

    return result;
}

int obtener_tamano_binario_productos(fstream& binario_productos) {
    binario_productos.seekg(0, ios::end);
    int result = (int)binario_productos.tellg()/sizeof(producto_t);
    binario_productos.clear();
    binario_productos.seekg(0, ios::beg);

    return result;
}

std::string obtener_nombre_binario_clientes(fstream& binario_clientes, int pos) {
    cliente_t cliente = {0};
    binario_clientes.seekg(pos * sizeof(cliente_t));
    binario_clientes.read((char*)&cliente, sizeof(cliente_t));
    binario_clientes.clear();
    binario_clientes.seekg(0, ios::beg);

    return cliente.nombre;
}

void clientes_merge(fstream& clientes1, const char* str1, fstream& clientes2, const char* str2, fstream& clientes) {
    int len = obtener_tamano_binario_clientes(clientes);
    int left_len = len/2;
    int right_len = len - left_len;
    int i = 0;
    int l = 0;
    int r = 0;

    while (l < left_len && r < right_len) {
        if (strcasecmp(obtener_nombre_binario_clientes(clientes1, l).c_str(), 
                       obtener_nombre_binario_clientes(clientes2, r).c_str()) < 0) 
        {
            set_binario_clientes(clientes, i, clientes1, l);
            i++;
            l++;
        } else {
            set_binario_clientes(clientes, i, clientes2, r);
            i++;
            r++;
        }
    }
    while (l < left_len) {
        set_binario_clientes(clientes, i, clientes1, l);
        i++;
        l++;
    }
    while (r < right_len) {
        set_binario_clientes(clientes, i, clientes2, r);
        i++;
        r++;
    }
    clientes1.close();
    clientes2.close();
    DELETE_FILE(str1);
    DELETE_FILE(str2);
}

void clientes_merge_sort(fstream& clientes, int itr) {
    int len = obtener_tamano_binario_clientes(clientes);
    if (len <= 1) {
        return;
    }

    int mid = len/2;
    fstream clientes1; 
    fstream clientes2; 

    cliente_t cliente = {0};
    char str1[128] = {0};
    char str2[128] = {0};
    snprintf(str1, 128, "clientes%d.bin", itr++);
    snprintf(str2, 128, "clientes%d.bin", itr++);

    clientes1.open(str1, ios::app | ios::binary);
    clientes2.open(str2, ios::app | ios::binary);
    if (!clientes1.is_open() && !clientes2.is_open()) {
        printf("Error clientes 1 y 2\n");
        exit(1);
    }

    int j = 0;
    for (int i = 0; i < len; i++) {
        clientes.read((char*)&cliente, sizeof(cliente_t));
        if (i < mid) {
            clientes1.write((char*)&cliente, sizeof(cliente_t));
        } else {
            clientes2.write((char*)&cliente, sizeof(cliente_t));
            j++;
        }
    }
    clientes1.close();
    clientes2.close();
    clientes1.open(str1, ios::in | ios::out | ios::binary);
    clientes2.open(str2, ios::in | ios::out | ios::binary);

    clientes_merge_sort(clientes1, itr);
    clientes_merge_sort(clientes2, itr);
    clientes_merge(clientes1, str1, clientes2, str2, clientes);
}

void agregar_cliente() {
    cliente_t cliente = {0};

    vector<cliente_t> clientes;

    fstream nombre;
    fstream cedula;
    fstream telefono;
    fstream direccion;

    nombre.open("nombres.txt", ios::in);
    if (!nombre.is_open()) {
        printf("Error abriendo nombres.txt\n");
    }
    cedula.open("cedulas.txt", ios::in);
    if (!cedula.is_open()) {
        printf("Error abriendo cedulas.txt\n");
    }
    telefono.open("telefonos.txt", ios::in);
    if (!telefono.is_open()) {
        printf("Error abriendo telefonos.txt\n");
    }
    direccion.open("direcciones.txt", ios::in);
    if (!direccion.is_open()) {
        printf("Error abriendo direcciones.txt\n");
    }

    size_t cnt = 0;
    while (cnt < 70) {
        std::string aux;

        std::getline(nombre, aux);
        strcpy(cliente.nombre, aux.c_str());

        std::getline(cedula, aux);
        cliente.id = stoi(aux);

        std::getline(telefono, aux);
        strcpy(cliente.telefono, aux.c_str());

        std::getline(direccion, aux);
        strcpy(cliente.direccion, aux.c_str());
        
        clientes.push_back(cliente);
        cnt++;
    }
    nombre.close();
    cedula.close();
    telefono.close();
    direccion.close();

    fstream binario;
    binario.open("clientes.bin", ios::out | ios::binary);

    for (int i = 0; i < clientes.size(); i++) {
        binario.write((char*)&clientes.at(i), sizeof(cliente_t));
    }
    binario.close();

    consultar_clientes();
}

void agregar_producto() {
    vector<producto_t> productos;
    fstream descripcion;

    descripcion.open("productos.txt", ios::in);
    if (!descripcion.is_open()) {
        printf("Error abriendo productos.txt\n");
    }

    size_t cnt = 0;
    while (cnt < 70) {
        producto_t producto = {0};
        std::string aux;

        std::getline(descripcion, aux);
        strcpy(producto.descripcion, aux.c_str());

        producto.id = cnt+1;

        producto.id_proveedor = std::rand()%21;

        producto.precio = (float)(std::rand()%200001+10)/(float)(std::rand()%1001+10);

        producto.stock = std::rand()%501+25;

        producto.stock_min = std::rand()%(int)(producto.stock/4)+8;
        
        productos.push_back(producto);
        cnt++;

    }
    descripcion.close();

    fstream binario;
    binario.open("productos.bin", ios::out | ios::binary);

    for (int i = 0; i < productos.size(); i++) {
        binario.write((char*)&productos.at(i), sizeof(producto_t));
    }
    binario.close();

    consultar_productos();
}

void consultar_clientes() {
    cliente_t cliente = {0};
    int cant_clientes = 0;
    fstream f;

    f.open("clientes.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("No existen clientes guardados!\n");
        f.close();
        return;
    }

    printf("____________________________________________________________________________________\n");
    printf("|                                     CLIENTES                                     |\n");
    printf("|__________________________________________________________________________________|\n");
    printf("|     ID     |       Nombre      |     Telefono    |           Direccion           |\n");
    printf("|----------------------------------------------------------------------------------|\n");

    f.read((char*)&cliente, sizeof(cliente_t));
    while(!f.eof()) {
        print_info_cliente(cliente);
        f.read((char*)&cliente, sizeof(cliente_t));

        cant_clientes++;
    }
    printf("-----------------------------------------------------------------------------------|\n");

    f.close();
}

void consultar_clientes(vector<cliente_t> clientes) {
    printf("____________________________________________________________________________________\n");
    printf("|                                     CLIENTES                                     |\n");
    printf("|__________________________________________________________________________________|\n");
    printf("|     ID     |       Nombre      |     Telefono    |           Direccion           |\n");
    printf("|----------------------------------------------------------------------------------|\n");

    for (cliente_t cliente : clientes) {
        print_info_cliente(cliente);
    } 
    printf("------------------------------------------------------------------------------------\n");

}


int consultar_productos() {
    producto_t producto = {0}; 
    int cant_productos = 0;
    fstream f;

    f.open("productos.bin", ios::binary | ios::in);
    if (!f.is_open()) {
        printf("No existen productos guardados\n");
        return -1;
    }

    printf("_________________________________________________________________________\n");
    printf("|                               PRODUCTOS                               |\n");
    printf("|_______________________________________________________________________|\n");
    printf("| ID  | ID Proveedor |   Descripcion   |  Precio | Stock | Stock minimo |\n");
    printf("|-----------------------------------------------------------------------|\n");

    f.read((char*)&producto, sizeof(producto_t));
    while (!f.eof()) {
        print_info_producto(producto);
        f.read((char*)&producto, sizeof(producto_t));
        cant_productos++;
    }
    printf("-------------------------------------------------------------------------\n");
    f.close();

    return cant_productos;
}

void consultar_productos(vector<producto_t> productos) {
    printf("_________________________________________________________________________\n");
    printf("|                               PRODUCTOS                               |\n");
    printf("|_______________________________________________________________________|\n");
    printf("| ID  | ID Proveedor |   Descripcion   |  Precio | Stock | Stock minimo |\n");
    printf("|-----------------------------------------------------------------------|\n");

    for (producto_t producto : productos) {
        print_info_producto(producto);
    } 
    printf("-------------------------------------------------------------------------\n");
}

void print_info_cliente(cliente_t cliente) {
    printf("| %-10d | %-17s | %-15s | %-29s |\n", cliente.id,
                                                  cliente.nombre,
                                                  cliente.telefono,
                                                  cliente.direccion);
}

void print_info_producto(producto_t producto) {
    printf("| %-3d | %-12d | %-15s | %-7.2f | %-5d | %-12d |\n", producto.id,
                                                                 producto.id_proveedor,
                                                                 producto.descripcion,
                                                                 producto.precio,
                                                                 producto.stock,
                                                                 producto.stock_min);
}

vector<producto_t> crear_vector_producto() {
    vector<producto_t> productos;
    producto_t producto = {0};
    fstream binario;
    binario.open("productos.bin", ios::in | ios::binary);


    binario.read((char*)&producto, sizeof(producto_t));
    while (!binario.eof()) {
        productos.push_back(producto);
        binario.read((char*)&producto, sizeof(producto_t));
    }

    return productos;
}

vector<cliente_t> crear_vector_clientes() {
    vector<cliente_t> clientes;
    cliente_t cliente = {0};
    fstream binario;
    binario.open("clientes.bin", ios::in | ios::binary);

    binario.read((char*)&cliente, sizeof(cliente_t));
    while (!binario.eof()) {
        clientes.push_back(cliente);
        binario.read((char*)&cliente, sizeof(cliente_t));
    }

    return clientes;
}

int vec_binary_search(vector<int> vec, int target) {
    int l = 0;
    int r = vec.size()-1;

    while (l <= r) {
        int m = (l+r)/2;
        if (vec.at(m) < target) {
            l = m+1;
        } else if (vec.at(m) > target) {
            r = m-1;
        } else {
            return m;
        }
    }
    return -1;
}

int clientes_binary_search(fstream& clientes, const char *target) {
    int len = obtener_tamano_binario_clientes(clientes);
    int l = 0;
    int r = len-1;

    while (l <= r) {
        cliente_t cliente = {0};
        int m = (l+r)/2;
        clientes.seekg(m * sizeof(cliente_t));
        clientes.read((char *)&cliente, sizeof(cliente_t));

        char c1 = tolower(cliente.nombre[0]);
        char c2 = tolower(target[0]);

        if (strcasecmp(cliente.nombre, target) < 0) {
            l = (m+1);// * sizeof(cliente_t);
        } else if (strcasecmp(cliente.nombre, target) > 0) {
            r = (m-1);// * sizeof(cliente_t);
        } else {
            return m;
        } 
    }
    return -1;
}

int vec_productos_binary_search(vector<producto_t> productos, const char *target) {
    int l = 0;
    int r = productos.size()-1;

    while (l <= r) {
        int m = (l+r)/2;
        if (strcasecmp(productos.at(m).descripcion, target) < 0) {
            l = m+1;
        } else if (strcasecmp(productos.at(m).descripcion, target) > 0) {
            r = m-1;
        } else {
            return m;
        } 
    }
    return -1;
}

int main(int argc, char *argv[]) {
    auto t1 = std::chrono::system_clock::now();
    std::srand(std::time(nullptr));
    vector<producto_t> productos = crear_vector_producto();

    vector<int> vec;
    int arr[] = {8, 2, 4, 7, 1, 3, 9, 6, 5, 10}; 
    vec.push_back(8);
    vec.push_back(2);
    vec.push_back(4);
    vec.push_back(7);
    vec.push_back(1);
    vec.push_back(3);
    vec.push_back(9);
    vec.push_back(6);
    vec.push_back(5);
    vec.push_back(10);

    vec_productos_quick_sort(&productos, 0, productos.size()-1);
    auto t2 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_secs = t2-t1;
    float tiempo_bubble = elapsed_secs.count();
    consultar_productos(productos);

    productos = crear_vector_producto();

    t1 = std::chrono::system_clock::now();
    productos_bubble_sort(&productos);
    t2 = std::chrono::system_clock::now();
    elapsed_secs = t2-t1;
    float tiempo_quick = elapsed_secs.count();
    consultar_productos(productos);

    productos = crear_vector_producto();

    t1 = std::chrono::system_clock::now();
    vec_productos_quick_sort(&productos, 0, productos.size()-1);
    t2 = std::chrono::system_clock::now();
    elapsed_secs = t2-t1;
    float tiempo_merge = elapsed_secs.count();
    consultar_productos(productos);
    int pos1 = vec_productos_binary_search(productos, "Cafe");
    printf("Posicion de melon: %d\n", pos1);


    printf("Tiempo de ordenacion alfabeticamente por quicksort: %lf\n", tiempo_bubble);
    printf("Tiempo de ordenacion alfabeticamente por bubble sort: %lf\n", tiempo_quick);
    printf("Tiempo de ordenacion alfabeticamente por merge sort: %lf\n", tiempo_merge);

//  vector<cliente_t> clientes = crear_vector_clientes();
//  consultar_clientes();
//  clientes_merge_sort(&clientes);
//  consultar_clientes(clientes);

//  consultar_clientes();
//  printf("\n\n\n\n");
//  fstream clientes;
//  clientes.open("clientes.bin", ios::in | ios::out | ios::binary);
//  binario_clientes_merge_sort(clientes, 0);
//  consultar_clientes();
//  int result = clientes_binary_search(clientes, "Emily Mitchell");
//  printf("result: %d\n", result);

//  if (result == -1) {
//      printf("No se ha encontrado a Zoe Miller");
//  } else {
//      printf("Se ha encontrado a Zoe Miller en la posicion: %d ", result);
//  }

//  vec_quick_sort(&vec, 0, vec.size()-1);
//  for (int i : vec) {
//      printf("%d ", i);
//  }
//  printf("\n");
//  int num = 4;
//  int pos = vec_binary_search(vec, num);
//  if (pos != -1) {
//      printf("element %d | pos %d\n", num, pos);
//  } else {
//      printf("element not found\n");
//  }
}
