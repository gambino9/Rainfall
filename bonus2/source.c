
// WARNING: Variable defined which should be unmapped: var_ch

undefined4 main(char **argv, char **envp)
{
    undefined4 uVar1;
    char *pcVar2;
    int32_t iVar3;
    undefined4 *puVar4;
    undefined4 *puVar5;
    uint8_t uVar6;
    char *arg_8h;
    undefined4 auStack96 [19];
    char *pcStack20;
    int32_t var_ch;
    
    uVar6 = 0;
    if (argv == (char **)0x3) {
        puVar4 = auStack96;
        for (iVar3 = 0x13; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar4 = 0;
            puVar4 = puVar4 + 1;
        }
        strncpy();
        strncpy();
        arg_8h = "LANG";
        pcVar2 = (char *)getenv();
        pcStack20 = pcVar2;
        if (pcVar2 != (char *)0x0) {
            iVar3 = memcmp();
            if (iVar3 == 0) {
                _language = 1;
                arg_8h = pcVar2;
            } else {
                arg_8h = pcStack20;
                iVar3 = memcmp();
                if (iVar3 == 0) {
                    _language = 2;
                }
            }
        }
        puVar4 = auStack96;
        puVar5 = (undefined4 *)&stack0xffffff50;
        for (iVar3 = 0x13; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar5 = *puVar4;
            puVar4 = puVar4 + (uint32_t)uVar6 * -2 + 1;
            puVar5 = puVar5 + (uint32_t)uVar6 * -2 + 1;
        }
        uVar1 = greetuser((int32_t)arg_8h);
    } else {
        uVar1 = 1;
    }
    return uVar1;
}



/* jsdec pseudo code output */
/* /home/lamia/bonus2 @ 0x80485a6 */
#include <stdint.h>
 
int32_t main (char ** argv, char ** envp) {
    int32_t var_ch;
    const char * src;
    size_t n;
    char * dest;
    char * s1;
    if (argv != 3) {
        eax = 1;
        goto label_0;
    }
    ebx = &dest;
    eax = 0;
    edx = 0x13;
    edi = ebx;
    ecx = edx;
    memset (edi, eax, ecx);
    eax = envp;
    eax += 4;
    eax = *(eax);
    eax = &dest;
    strncpy (eax, 0x28, eax);
    eax = envp;
    eax += 8;
    eax = *(eax);
    eax = &dest;
    eax += 0x28;
    strncpy (eax, 0x20, eax);
    eax = getenv ("LANG");
    s1 = eax;
    if (s1 != 0) {
        eax = s1;
        eax = memcmp (eax, 2, 0x804873d);
        if (eax == 0) {
            *(language) = 1;
        } else {
            eax = s1;
            eax = memcmp (eax, 2, 0x8048740);
            if (eax != 0) {
                goto label_1;
            }
            *(language) = 2;
        }
    }
label_1:
    edx = esp;
    ebx = &dest;
    eax = 0x13;
    edi = edx;
    esi = ebx;
    ecx = eax;
    do {
        *(es:edi) = *(esi);
        ecx--;
        esi += 4;
        es:edi += 4;
    } while (ecx != 0);
    greetuser ();
label_0:
    esp = &var_ch;
    return eax;
}





// WARNING: Could not reconcile some variable overlaps

void greetuser(int32_t arg_8h)
{
    char *s1;
    uint32_t uStack72;
    undefined4 uStack68;
    uint32_t uStack64;
    undefined2 uStack60;
    char cStack58;
    
    if (_language == 1) {
        s1 = str.Hyv_____p__iv._0_4_;
        uStack72 = str.Hyv_____p__iv._4_4_;
        uStack68 = str.Hyv_____p__iv._8_4_;
        uStack64 = str.Hyv_____p__iv._12_4_;
        uStack60 = str.Hyv_____p__iv._16_2_;
        cStack58 = str.Hyv_____p__iv[18];
    } else if (_language == 2) {
        s1 = str.Goedemiddag._0_4_;
        uStack72 = str.Goedemiddag._4_4_;
        uStack68 = str.Goedemiddag._8_4_;
        uStack64 = uStack64 & 0xffff0000 | (uint32_t)str.Goedemiddag._12_2_;
    } else if (_language == 0) {
        s1 = str.Hello._0_4_;
        uStack72._0_3_ = CONCAT12(str.Hello[6], str.Hello._4_2_);
        uStack72 = uStack72 & 0xff000000 | (uint32_t)(unkuint3)uStack72;
    }
    strcat(&s1, &arg_8h);
    puts(&s1);
    return;
}


/* jsdec pseudo code output */
/* /home/lamia/bonus2 @ 0x8048484 */
#include <stdint.h>
 
int32_t greetuser (int32_t arg_8h) {
    char * s1;
    const char * s2;
    eax = language;
    if (eax != 1) {
        if (eax != 2) {
            if (eax != 0) {
                goto label_0;
            }
            edx = "Hello ";
            eax = &s1;
            ecx = *(edx);
            *(eax) = ecx;
            ecx = *((edx + 4));
            *((eax + 4)) = cx;
            edx = *((edx + 6));
            *((eax + 6)) = dl;
            edx = "Hyv\xc3\xa4\xc3\xa4 p\xc3\xa4iv\xc3\xa4\xc3\xa4 ";
            eax = &s1;
            ecx = *(edx);
            *(eax) = ecx;
            ecx = *((edx + 4));
            *((eax + 4)) = ecx;
            ecx = *((edx + 8));
            *((eax + 8)) = ecx;
            ecx = *((edx + 0xc));
            *((eax + 0xc)) = ecx;
            ecx = *((edx + 0x10));
            *((eax + 0x10)) = cx;
            edx = *((edx + 0x12));
            *((eax + 0x12)) = dl;
        } else {
        } else {
            edx = "Goedemiddag! ";
            eax = &s1;
            ecx = *(edx);
            *(eax) = ecx;
            ecx = *((edx + 4));
            *((eax + 4)) = ecx;
            ecx = *((edx + 8));
            *((eax + 8)) = ecx;
            edx = *((edx + 0xc));
            *((eax + 0xc)) = dx;
        }
    }
label_0:
    eax = &arg_8h;
    eax = &s1;
    strcat (eax, eax);
    eax = &s1;
    puts (eax);
    return eax;
}
