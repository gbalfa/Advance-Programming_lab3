#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*given two integers, returns the lesser value of the pair*/
int min(int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}

/* given an array of 12 integers, returns the lesser value*/
int findMin(int *a) {
  int result = a[0];
  for (int i = 1; i < 12; i++) {
    result = min(result, a[i]);
  }
  return result;
}

/*returns the position of the first occurrence of the value "a" in the array arr
 */
int findPos(int a, int *arr) {
  for (int i = 0; i < 11; i++) {
    if (arr[i] == a) {
      return i;
    }
  }
  return -1;
}

/*given a position and an array of 12 integers
  returns the value and the position of the cheaper value to traverse
  the stairs
*/
int *compareFloor(int pos, int *floor) {
  int *result = (int *)malloc(sizeof(int) * 2);
  int aux;
  result[1] = 0;
  result[0] = min(abs(pos - 0), 12 - abs(pos - 0)) + floor[0];
  for (int i = 1; i < 12; i++) {
    aux = (min(abs(pos - i), 12 - abs(pos - i)) + floor[i]);
    if (aux < result[0]) {
      result[0] = aux;
      result[1] = i;
    }
  }
  return result;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf(
        "Número incorrecto de argumentos, pruebe con \"./a.out "
        "M.tex\"\n");
    return 0;
  }
  double time_spent;
  clock_t begin, end;
  int pos;
  int result;
  int *aux;
  int printingPath[96];
  FILE *archivo;
  int building[96][12];
  int path[96][12];
  archivo = fopen(argv[1], "r");
  for (int j = 0; j < 96; j++) /*reading the file... */
  {
    for (int i = 0; i < 12; i++) {
      fscanf(archivo, "%d", &building[j][i]);
    }
  }
  fclose(archivo);
  time_spent = 0.0;
  begin = clock();
  for (int i = 0; i < 12; i++) /* setting up the first floor...*/
  {
    building[0][i] = building[0][i] + min(i, 12 - i);
    path[0][i] = i;
  }

  for (int j = 1; j < 96; j++) /* using the "minimal descent algorithm*/
  {
    for (int i = 0; i < 12; i++) {
      aux = compareFloor(i, building[j - 1]);
      building[j][i] = aux[0] + building[j][i];
      path[j][i] = aux[1];
      free(aux);
    }
  }
  result = findMin(
      building[95]); /*printing the minimal cost of reaching the top level*/

  end = clock();
  time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Time elapsed is %f seconds", time_spent);
  printf("\nCosto camino mínimo: %d\n", result);
  pos = findPos(result, building[95]);
  for (int k = 95; k >= 0; k--) /* setting the printing path*/
  {
    printingPath[k] = pos + 1;
    pos = path[k][pos];
  }
  printf("Camino:\n");
  for (int k = 0; k < 96; k++) {
    printf("%d ", printingPath[k]); /* printing the optimal path */
  }
  printf("\n");
  return 0;
}
