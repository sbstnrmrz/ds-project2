// Participantes: 
// Sebastian Ramirez C.I:31567908
// Angel Vivas       C.I:30890743

#include "defs.h"

void consultar_clientes(fstream& f) {
    cliente_t cliente = {0};
    f.seekg(0, ios::beg);

    printf("____________________________________________________________________________________\n");
    printf("|                                     CLIENTES                                     |\n");
    printf("|__________________________________________________________________________________|\n");
    printf("|     ID     |       Nombre      |     Telefono    |           Direccion           |\n");
    printf("|----------------------------------------------------------------------------------|\n");

    f.read((char*)&cliente, sizeof(cliente_t));
    while(!f.eof()) {
        print_info_cliente(cliente);
        f.read((char*)&cliente, sizeof(cliente_t));

    }
    printf("-----------------------------------------------------------------------------------|\n");

    f.clear();
    f.seekg(0, ios::beg);
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

void set_binario_clientes(fstream& clientes1, int pos1, fstream& clientes2, int pos2) {
    cliente_t tmp_cliente = {0};

    clientes2.seekg(pos2 * sizeof(cliente_t));
    clientes2.read((char*)&tmp_cliente, sizeof(cliente_t));

    clientes1.seekp(pos1 * sizeof(cliente_t));
    clientes1.write((char*)&tmp_cliente, sizeof(cliente_t));
}

int obtener_tamano_clientes(fstream& clientes) {
    clientes.seekg(0, ios::end);
    int result = (int)clientes.tellg()/sizeof(cliente_t);
    clientes.clear();
    clientes.seekg(0, ios::beg);

    return result;
}

std::string obtener_nombre_clientes(fstream& clientes, int pos) {
    cliente_t cliente = {0};
    clientes.seekg(pos * sizeof(cliente_t));
    clientes.read((char*)&cliente, sizeof(cliente_t));
    clientes.clear();
    clientes.seekg(0, ios::beg);

    return cliente.nombre;
}

std::string obtener_nombre_productos(fstream& productos, int pos) {
    producto_t producto = {0};
    productos.seekg(pos * sizeof(producto_t));
    productos.read((char*)&producto, sizeof(producto_t));
    productos.clear();
    productos.seekg(0, ios::beg);

    return producto.descripcion;
}

void clientes_mezcla(fstream& clientes1, const char* str1, fstream& clientes2, const char* str2, fstream& clientes) {
    int len = obtener_tamano_clientes(clientes);
    int left_len = len/2;
    int right_len = len - left_len;
    int i = 0;
    int l = 0;
    int r = 0;

    while (l < left_len && r < right_len) {
        if (strcasecmp(obtener_nombre_clientes(clientes1, l).c_str(), 
                       obtener_nombre_clientes(clientes2, r).c_str()) < 0) 
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

void clientes_mezcla_directa(fstream& clientes, int itr) {
    int len = obtener_tamano_clientes(clientes);
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

    clientes_mezcla_directa(clientes1, itr);
    clientes_mezcla_directa(clientes2, itr);
    clientes_mezcla(clientes1, str1, clientes2, str2, clientes);
}

void clientes_mezcla_natural(fstream& clientes) {
    int len = obtener_tamano_clientes(clientes);
    printf("len: %d\n", len);

    fstream clientes1;
    fstream clientes2;

    int i = 0;
    int j = 0;
    int k = 0;
    bool ordenado = false;

    clientes1.open("clientes1.bin", ios::app | ios::binary);
    clientes2.open("clientes2.bin", ios::app | ios::binary);
    while (!ordenado) {
        cliente_t cliente = {0};
        if (strcasecmp(obtener_nombre_clientes(clientes, i).c_str(), 
                       obtener_nombre_clientes(clientes, i+1).c_str()) < 0) 
        {
            clientes.seekg(i * sizeof(cliente_t));
            clientes.read((char*)&cliente, sizeof(cliente_t));
            printf("nombre: %s\n", cliente.nombre);
            clientes1.write((char*)&cliente, sizeof(cliente_t));
            i++;
            printf("i: %d\n", i);
            if (i >= len-2) {
                printf("ASDSADASDSADASDSAADS\n");
                clientes.seekg(i * sizeof(cliente_t));
                clientes.read((char*)&cliente, sizeof(cliente_t));
                clientes1.write((char*)&cliente, sizeof(cliente_t));
//                clientes.seekg(0, ios::beg);
                i = 0;
            } else {
                continue;
            }
        } else {
            clientes.seekg(i * sizeof(cliente_t));
            clientes.read((char*)&cliente, sizeof(cliente_t));
            printf("nombre: %s\n", cliente.nombre);
            clientes1.write((char*)&cliente, sizeof(cliente_t));
            i++;
            while (true) {
                if (strcasecmp(obtener_nombre_clientes(clientes, i).c_str(), 
                               obtener_nombre_clientes(clientes, i+1).c_str()) < 0) 
                {
                    clientes.seekg(i * sizeof(cliente_t));
                    clientes.read((char*)&cliente, sizeof(cliente_t));
                    clientes2.write((char*)&cliente, sizeof(cliente_t));
                    i++;
                    printf("i: %d\n", i);
                    if (i >= len-2) {
                        clientes.seekg(i * sizeof(cliente_t));
                        clientes.read((char*)&cliente, sizeof(cliente_t));
                        clientes2.write((char*)&cliente, sizeof(cliente_t));
                        i = 0;
//                        clientes.clear();
//                        clientes.seekg(0, ios::beg);
                        printf("ASDSADASD\n");
                        break;
                    } 
                } else { 
                    clientes.seekg(i * sizeof(cliente_t));
                    clientes.read((char*)&cliente, sizeof(cliente_t));
                    clientes2.write((char*)&cliente, sizeof(cliente_t));
                    i++;
                    break;
                }
            }
        }
        int l = 0;
        int r = 0;
        if (k >= len-1) {
            k = 0;
        }

        clientes1.close();
        clientes2.close();
        clientes1.open("clientes1.bin", ios::in | ios::out | ios::binary);
        clientes2.open("clientes2.bin", ios::in | ios::out | ios::binary);
        if (!clientes1.is_open()) {
            printf("XD\n");
            exit(1);
        }
        if (!clientes2.is_open()) {
            printf("XD\n");
            exit(1);
        }
        
        consultar_clientes(clientes1);
        consultar_clientes(clientes2);
//      static int a = 0;
//      SLEEP(0.2);
//      if (a == 25) {
//          exit(1);
//      }
//      a++;

        int len1 = obtener_tamano_clientes(clientes1);
        int len2 = obtener_tamano_clientes(clientes2);
        printf("len1: %d | len2: %d\n", len1, len2);

        while (l < len1 && r < len2) {
            auto str1 = obtener_nombre_clientes(clientes1, l).c_str();
            auto str2 = obtener_nombre_clientes(clientes2, r).c_str();
            printf("COMPARACION: %s < %s\n", str1, str2);
            if (strcasecmp(obtener_nombre_clientes(clientes1, l).c_str(), 
                           obtener_nombre_clientes(clientes2, r).c_str()) < 0) 
            {
                set_binario_clientes(clientes, k, clientes1, l);
                l++;
                k++;
            } else {
                set_binario_clientes(clientes, k, clientes2, r);
                r++;
                k++;
            }
        }
        while (l < len1) {
            set_binario_clientes(clientes, k, clientes1, l);
            l++;
            k++;
        }
        while (r < len2) {
            set_binario_clientes(clientes, k, clientes2, r);
            r++;
            k++;
        }
        printf("WARIO\n");
        clientes1.close();
        clientes2.close();
        DELETE_FILE("clientes1.bin");
        DELETE_FILE("clientes2.bin");

        int check = 0;
        for (int n = 0; n < len-1; n++) {
            if (strcasecmp(obtener_nombre_clientes(clientes, n).c_str(), 
                           obtener_nombre_clientes(clientes, n+1).c_str()) < 0) 
            {
                check++;  
            } else {
                break;
            }
        }
        printf("check: %d\n", check);
        if (check >= len-2) {
            break;
        }

        clientes1.open("clientes1.bin", ios::app | ios::binary);
        clientes2.open("clientes2.bin", ios::app | ios::binary);
    }
}

void vec_mezcla_natural(vector<int> *vec) {
    int len = vec->size();
    vector<int> vec1;
    vector<int> vec2;

    int i = 0;
    int j = 0;
    int k = 0;
    bool ordenado = false;

    printf("vector desordenado: ");
    for (int i : *vec) {
        printf("%d ", i);
    }
    printf("\n");

    while (!ordenado) {
        if (vec->at(i) < vec->at(i+1)) {
            vec1.push_back(vec->at(i));
            i++;
            if (i >= vec->size()-1) {
                vec1.push_back(vec->at(i));
                i = 0;
            } else {
                continue;
            }
        } else {
            vec1.push_back(vec->at(i));
            i++;
            while (true) {
                if (vec->at(i) < vec->at(i+1)) {
                    vec2.push_back(vec->at(i));
                    i++;
                    if (i >= vec->size()-1) {
                        vec2.push_back(vec->at(i));
                        i = 0;
                        break;
                    } 
                } else { 
                    vec2.push_back(vec->at(i));
                    i++;
                    break;
                }
            }
        }
        int l = 0;
        int r = 0;
        if (k >= vec->size()-1) {
            k = 0;
        }
        while (l < vec1.size() && r < vec2.size()) {
            if (vec1.at(l) < vec2.at(r)) {
                vec->at(k) = vec1.at(l);
                l++;
                k++;
            } else {
                vec->at(k) = vec2.at(r);
                r++;
                k++;
            }
        }
        while (l < vec1.size()) {
            vec->at(k) = vec1.at(l);
            l++;
            k++;
        }
        while (r < vec2.size()) {
            vec->at(k) = vec2.at(r);
            r++;
            k++;
        }
        vec1.clear();
        vec2.clear();

        int check = 0;
        for (int n = 0; n < vec->size()-1; n++) {
            if (vec->at(n) < vec->at(n+1)) {
                check++;  
            } else {
                break;
            }
        }
        if (check == vec->size()-1) {
            break;
        }
    }
    printf("vector ordenado: ");
    for (int i : *vec) {
        printf("%d ", i);
    }
    printf("\n");
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

vector<producto_t> crear_vector_productos() {
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

int vec_productos_binary_search(vector<producto_t> vec, const char *target) {
    int l = 0;
    int r = vec.size()-1;

    while (l <= r) {
        int m = (l+r)/2;
        const char *str = vec.at(m).descripcion; 
        if (strcasecmp(str, target) < 0) {
            l = (m+1);
        } else if (strcasecmp(str, target) > 0) {
            r = (m-1);
        } else {
            return m;
        } 
    }
    return -1;
}

int clientes_binary_search(fstream& clientes, const char *target) {
    int len = obtener_tamano_clientes(clientes);

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

int main(int argc, char *argv[]) {
    auto t1 = std::chrono::system_clock::now();
    std::srand(std::time(nullptr));
    
    vector<producto_t> vec_productos = crear_vector_productos();

    printf("UNSORTED\n");
    consultar_productos(vec_productos);
    vec_productos_quick_sort(&vec_productos, 0, vec_productos.size()-1);

    auto t2 = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_secs = t2-t1;
    float tiempo_quick_sort = elapsed_secs.count();

    printf("SORTED\n\n\n");
    consultar_productos(vec_productos);

    printf("Tiempo de ordenacion de productos alfabeticamente por quicksort: %lf\n\n", tiempo_quick_sort);
    
    const char *str = "melon";
    printf("Binary search: %s, pos: %d\n", str, vec_productos_binary_search(vec_productos, str));

    vector<int> vec;
    vec.push_back(3);
    vec.push_back(5);
    vec.push_back(9);
    vec.push_back(12);
    vec.push_back(31);
    vec.push_back(11);
    vec.push_back(2);
    vec.push_back(17);
    vec.push_back(19);
    vec.push_back(1);
    vec.push_back(6);
    vec.push_back(4);
    vec.push_back(7);
    vec.push_back(8);

    for (int i : vec) {
        printf("%d ", i);
    }
    printf("\n\n");
    vec_mezcla_natural(&vec);

    fstream clientes;
    consultar_clientes();
    clientes.open("clientes.bin", ios::in | ios::out | ios::binary);
    clientes_mezcla_natural(clientes);
    consultar_clientes();
}
