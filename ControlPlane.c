#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint32_t ip;
    uint32_t cidr;
    uint32_t subnet_mask;
    uint32_t network_id;
    uint32_t broadcast_id;
} NetCalcResult;

// 1. Parametre (RCX): ip_num
// 2. Parametre (RDX): cidr
// 3. Parametre (R8) : struct pointer 
extern void calculate_network_asm(uint32_t ip, uint32_t cidr, NetCalcResult *result);

void print_ip(const char *label, uint32_t ip) {
    printf("%-15s : %u.%u.%u.%u\n", label,
        (ip >> 24) & 0xFF,
        (ip >> 16) & 0xFF,
        (ip >> 8)  & 0xFF,
        ip & 0xFF);
}

void print_binary(const char *label, uint32_t ip) {
    printf("%-15s : ", label);
    // 31. bitten 0. bite kadar tek tek kontrol ediyoruz
    for (int i = 31; i >= 0; i--) {
        uint32_t bit = (ip >> i) & 1;
        printf("%u", bit);

        // Her 8 bitte bir nokta koy
        if (i > 0 && i % 8 == 0) {
            printf(".");
        }
    }
    printf("\n");
}

int main() {
    unsigned int o1, o2, o3, o4, cidr;

    printf("=== CONTROL PLANE: IP ve CIDR Girisi ===\n");
    printf("IP Adresini girin (Orn: 192.168.1.10): ");
    if (scanf("%u.%u.%u.%u", &o1, &o2, &o3, &o4) != 4) {
        printf("Hatali IP format!\n");
        return 1;
    }

    printf("CIDR degerini girin (0-32 arasi, Orn: 24): ");
    if (scanf("%u", &cidr) != 1 || cidr > 32) {
        printf("Hatali CIDR degeri!\n");
        return 1;
    }

    // IP oktetlerini 32-bit tek bir Uint32 sayıya birleştirme
    uint32_t ip_num = (o1 << 24) | (o2 << 16) | (o3 << 8) | o4;

    NetCalcResult result;

    printf("\n[Control Plane] Veriler Data Plane'e (Assembly) gonderiliyor...\n");
    
    // Assembly Çağırıyoruz
    calculate_network_asm(ip_num, cidr, &result);

    printf("[Data Plane] Hesaplama tamamlandi. Sonuclar:\n\n");

    printf("=== DECIMAL (ONDALIK) GOSTERIM ===\n");
    print_ip("IP Adresi", result.ip);
    printf("%-15s : /%u\n", "CIDR", result.cidr);
    print_ip("Subnet Mask", result.subnet_mask);
    print_ip("Network ID", result.network_id);
    print_ip("Broadcast ID", result.broadcast_id);

    printf("\n");

    printf("=== BINARY (IKILIK) GOSTERIM ===\n");
    print_binary("IP Adresi", result.ip);
    print_binary("Subnet Mask", result.subnet_mask);
    print_binary("Network ID", result.network_id);
    print_binary("Broadcast ID", result.broadcast_id);

    printf("\nCikmak icin ENTER tusuna basin...");
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // scanf'ten kalan '\n' karakterini temizle
    getchar(); 

    return 0;
}