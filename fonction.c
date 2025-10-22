#include <stdio.h>
#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

float func_addition() {
    float nb1, nb2;
    printf("Entrez le premier nombre : ");
    scanf("%f", &nb1);
    printf("Entrez le deuxième nombre : ");
    scanf("%f", &nb2);
    return nb1 + nb2;
}

float func_soustraction() {
    float nb1, nb2;
    printf("Entrez le premier nombre : ");
    scanf("%f", &nb1);
    printf("Entrez le deuxième nombre : ");
    scanf("%f", &nb2);
    return nb1 - nb2;
}

float func_multiplication() {
    float nb1, nb2;
    printf("Entrez le premier nombre : ");
    scanf("%f", &nb1);
    printf("Entrez le deuxième nombre : ");
    scanf("%f", &nb2);
    return nb1 * nb2;
}

float func_division() {
    float nb1, nb2;
    printf("Entrez le premier nombre : ");
    scanf("%f", &nb1);
    printf("Entrez le deuxième nombre : ");
    scanf("%f", &nb2);
    if (nb2 == 0) {
        printf("Erreur : division par zéro !\n");
        return 0;
    }
    return nb1 / nb2;
}

float func_square () {
    float nb;
    printf("Entrez le nombre : ");
    scanf("%f", &nb);
    return nb * nb;
}

float func_square_root () {
    float nb;
    printf("Entrez le nombre : ");
    scanf("%f", &nb);
    if (nb < 0) {
        printf("Erreur : racine carrée d'un nombre négatif !\n");
        return 0;
    }
    return sqrt(nb);
}

float func_power () {
    float base, exponent;
    printf("Entrez la base : ");
    scanf("%f", &base);
    printf("Entrez l'exposant : ");
    scanf("%f", &exponent);
    return pow(base, exponent);
}

float func_modulus () {
    int nb1, nb2;
    printf("Entrez le premier nombre (entier) : ");
    scanf("%d", &nb1);
    printf("Entrez le deuxième nombre (entier) : ");
    scanf("%d", &nb2);
    if (nb2 == 0) {
        printf("Erreur : division par zéro !\n");
        return 0;
    }
    return nb1 % nb2;
}

float func_factorial () {
    int nb;
    unsigned long long fact = 1;
    printf("Entrez un nombre entier non négatif : ");
    scanf("%d", &nb);
    if (nb < 0) {
        printf("Erreur : factorielle d'un nombre négatif !\n");
        return 0;
    }
    for (int i = 1; i <= nb; ++i) {
        fact *= i;
    }
    return fact;
}

double func_logarithm(void) {
    double nb;
    printf("Entrez un nombre positif : ");
    if (scanf("%lf", &nb) != 1) {
        printf("Erreur de lecture.\n");
        return 0.0;
    }

    if (nb <= 0.0) {
        printf("Erreur : logarithme d'un nombre non positif !\n");
        return 0.0;
    }
    if (!isfinite(nb)) {
        return INFINITY;
    }

    int e;
    double m = frexp(nb, &e);
    const double INV_SQRT2 = 0.7071067811865475244; 
    if (m < INV_SQRT2) {
        m *= 2.0;
        e -= 1;
    }
    double t  = (m - 1.0) / (m + 1.0);
    double t2 = t * t;
    double sum  = t;
    double term = t;

    for (int k = 3; k <= 51; k += 2) {
        term *= t2;            // t^(k)
        double add = term / (double)k;
        sum += add;
        if (fabs(add) < 1e-16)
            break;
    }
    double ln_m = 2.0 * sum;
    const double LN2 = 0.6931471805599453094;
    double result = e * LN2 + ln_m;
    printf("ln(%.17g) = %.17g\n", nb, result);
    return result;
}

float func_exponential(void) {
    double x;
    printf("Entrez un nombre : ");
    if (scanf("%lf", &x) != 1) {
        printf("Erreur de lecture.\n");
        return 0.0;
    }

    if (x > 709.782712893384) { 
        printf("Erreur : dépassement de capacité pour exp(%.17g) !\n", x);
        return INFINITY;
    }
    if (x < -745.1332191019411) { 
        return 0.0; 
    }

    int n = (int)(x / 0.6931471805599453); 
    double r = x - n * 0.6931471805599453; 

    double term = 1.0; 
    double sum = 1.0; 
    for (int k = 1; k <= 50; ++k) {
        term *= r / k; 
        sum += term;
        if (fabs(term) < 1e-16)
            break;
    }

    double result = sum * pow(2.0, n); 
    printf("exp(%.17g) = %.17g\n", x, result);
    return result;
}

float func_sine(void) {
    double x;
    printf("Entrez un angle en radians : ");
    if (scanf("%lf", &x) != 1) {
        printf("Erreur de lecture.\n");
        return 0.0;
    }

    x = fmod(x, 2.0 * M_PI); 

    double term = x; 
    double sum = x; 
    for (int k = 1; k <= 50; ++k) {
        term *= -x * x / ((2 * k) * (2 * k + 1)); 
        sum += term;
        if (fabs(term) < 1e-16)
            break;
    }

    printf("sin(%.17g) = %.17g\n", x, sum);
    return sum;
}

float func_cosine(void) {
    double x;
    printf("Entrez un angle en radians : ");
    if (scanf("%lf", &x) != 1) {
        printf("Erreur de lecture.\n");
        return 0.0;
    }

    x = fmod(x, 2.0 * M_PI); 

    double term = 1.0; 
    double sum = 1.0; 
    for (int k = 1; k <= 50; ++k) {
        term *= -x * x / ((2 * k - 1) * (2 * k)); 
        sum += term;
        if (fabs(term) < 1e-16)
            break;
    }

    printf("cos(%.17g) = %.17g\n", x, sum);
    return sum;
}

float func_tangent(void) {
    double x;
    printf("Entrez un angle en radians : ");
    if (scanf("%lf", &x) != 1) {
        printf("Erreur de lecture.\n");
        return 0.0;
    }

    x = fmod(x, 2.0 * M_PI); 

    double term_sin = x; 
    double sum_sin = x; 
    for (int k = 1; k <= 50; ++k) {
        term_sin *= -x * x / ((2 * k) * (2 * k + 1)); 
        sum_sin += term_sin;
        if (fabs(term_sin) < 1e-16)
            break;
    }

    double term_cos = 1.0; 
    double sum_cos = 1.0; 
    for (int k = 1; k <= 50; ++k) {
        term_cos *= -x * x / ((2 * k - 1) * (2 * k)); 
        sum_cos += term_cos;
        if (fabs(term_cos) < 1e-16)
            break;
    }

    if (fabs(sum_cos) < 1e-16) {
        printf("Erreur : tangente indéfinie pour cet angle !\n");
        return 0.0;
    }

    double result = sum_sin / sum_cos;
    printf("tan(%.17g) = %.17g\n", x, result);
    return result;
}

float func_percentage() {
    float total, portion;
    printf("Entrez le montant total : ");
    scanf("%f", &total);
    printf("Entrez la portion : ");
    scanf("%f", &portion);
    if (total == 0) {
        printf("Erreur : le montant total ne peut pas être zéro !\n");
        return 0;
    }
    return (portion / total) * 100;
}

float func_fibonacci() {
    int n;
    printf("Entrez la position dans la séquence de Fibonacci (entier non négatif) : ");
    scanf("%d", &n);
    if (n < 0) {
        printf("Erreur : position négative !\n");
        return 0;
    }
    if (n == 0) return 0;
    if (n == 1) return 1;

    unsigned long long a = 0, b = 1, fib;
    for (int i = 2; i <= n; ++i) {
        fib = a + b;
        a = b;
        b = fib;
    }
    printf("Le nombre de Fibonacci à la position %d est %llu\n", n, fib);
    return 0;
}

float func_pgcd() {
    int a, b;
    printf("Entrez le premier nombre entier : ");
    scanf("%d", &a);
    printf("Entrez le deuxième nombre entier : ");
    scanf("%d", &b);
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    printf("Le PGCD est %d\n", a);
    return 0;
}

float func_pcm() {
    int a, b;
    printf("Entrez le premier nombre entier : ");
    scanf("%d", &a);
    printf("Entrez le deuxième nombre entier : ");
    scanf("%d", &b);
    if (a == 0 || b == 0) {
        printf("Erreur : le PPCM n'est pas défini pour zéro !\n");
        return 0;
    }
    int original_a = a, original_b = b;
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    int gcd = a;
    int lcm = (original_a / gcd) * original_b; 
    printf("Le PPCM est %d\n", lcm);
    return 0;
}


