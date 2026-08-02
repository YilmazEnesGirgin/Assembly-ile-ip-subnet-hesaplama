section .text
    global calculate_network_asm

; Şablon bu şekilde :
; void calculate_network_asm(uint32_t ip [ECX], uint32_t cidr [EDX], NetCalcResult *result [R8])
; Struct hafıza dizilimi (Her biri 4 byte / 32-bit):
; [R8 + 0]  = ip
; [R8 + 4]  = cidr
; [R8 + 8]  = subnet_mask
; [R8 + 12] = network_id
; [R8 + 16] = broadcast_id

calculate_network_asm:
    ;  Gelen orijinal değerleri struct içindeki yerlerine yerleştirdik. 
    mov     [r8 + 0], ecx         ; result->ip = ip
    mov     [r8 + 4], edx         ; result->cidr = cidr

    ; 2. Subnet Mask Hesaplama
    ; Mantık: 32 bitlik 1 serisini (0xFFFFFFFF) (32 - CIDR) kadar sağa kaydırıp tersini almak
    mov     eax, 32
    sub     eax, edx              ; EAX = 32 - CIDR yani sıfırlamamız gerekn bit syısını bulduk
    
    ; Eğer CIDR == 32 direkt mask 0xFFFFFFFF olur
    test    eax, eax        
    jz      .cidr_32

    mov     r9d, 0xFFFFFFFF
    mov     ecx, eax              
    shl     r9d, cl               
    jmp     .mask_ready

.cidr_32:
    mov     r9d, 0xFFFFFFFF

.mask_ready:
    mov     [r8 + 8], r9d         



    ; 3. Network ID Hesaplama 
    mov     eax, [r8 + 0]          
    and     eax, r9d               
    mov     [r8 + 12], eax        



    ; 4. Broadcast ID Hesaplama 
    not     r9d                    
    or      eax, r9d              
    mov     [r8 + 16], eax        

    ret