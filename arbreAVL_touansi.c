#include<stdio.h>
#include<stdlib.h>
#include <assert.h>
#include "arbreAVL.h"

/* Fonction utilitaire pour recuperer la hauteur d'un arbre
   NB : Renvoie 0 si node est NULL
*/
int height(struct Node *node)
{
  if (!node)
    return 0;
  return node->height;
}

/* Fonction utilitaire renvoyant le maximum de deux entiers
 */
int max(int a, int b)
{
  return (a > b)? a : b;
}

/* Procedure qui recalcule le champs height de node a partir de la
   hauteur de ses noeuds fils
*/
void updateHeight(struct Node *node) {
  // Conseil : combinez les fonction height() et max() pour simplifier le codage de updateHeight()
  node->height = max(height(node->left), height(node->right)) + 1;
}

/* Fonction renvoyant le nombre de noeuds dans le sous-arbre node
   NB : Renvoie 0 si l'arbre ne contient pas de noeud
*/
int nbNode(const struct Node* node)
{
  if (!node)
    return 0;
  else
      return 1 + nbNode(node->left) + nbNode(node->right);
}

/* Fonction liberant tous les elements du sous-arbre node
   (y compris node)
   Renvoie systematiquement NULL
*/
struct Node *release(struct Node *node)
{
  if (node)
  {
    release(node->left);
    release(node->right);
    free(node->key); //liberation de la memoire allouee pour copier la cle
    free(node);
  }
  return NULL;
}

/* Fonction (interne) pour creer un noeud pour stocker la cle
   NB :
      - La cle est recopiee dans une zone memoire allouee dans newNode
      - Les pointeurs left et right sont a NULL
      - Le champ height est initialise a 1 (ce noeud est considere comme
        une feuille autonome).
*/
static struct Node* newNode(const char *key, char *value)
{
  struct Node* node = malloc(sizeof(struct Node));
  node->key = malloc(strlen(key) + 1);
  strcpy(node->key, key);
  node->value = malloc(strlen(value) + 1);
  strcpy(node->value, value);
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
}

/* Fonction qui fait la rotation a droite pour l'equilibrage
  de l'arbre avl
*/
static struct Node *rightRotate(struct Node *z)
{
  struct Node *y = z->left;
  z->left = y->right;
  y->right = z;
  updateHeight(z);
  updateHeight(y);
  return y;
}

/* Fonction qui fait la rotation a gauche pour l'equilibrage
  de l'arbre avl
*/
static struct Node *leftRotate(struct Node *z)
{
  struct Node *y = z->right;
  z->right = y->left;
  y->left = z;
  updateHeight(z);
  updateHeight(y);
  return y;
}

/* Fonction recursive qui insere key dans le sous-arbre de racine node.
   Renvoie la nouvelle racine de ce sous-arbre.
   NB : 1) un arbre binaire ne contient jamais deux fois la meme valeur.
           De ce fait, si la valeur existe deja, insert renvoie node, sans creer
           de nouveau noeud.
        2) Si node vaut NULL, renvoie un arbre constitue uniquement d'un noeud
           contenant cet arbre.
*/
struct Node* insert(struct Node* node, const char* key, char *value)
{
  if (!node)
    return newNode(key, value);
  else
  {
    if (strcmp(key, node->key) < 0)
      node->left = insert(node->left, key, value);
    else if (strcmp(key, node->key) > 0)
      node->right = insert(node->right, key, value);
    else if (strcmp(key, node->key) == 0)
    {
      node->value = realloc(node->value, strlen(value) + 1);
      strcpy(node->value, value);
      return node;
    }
  }
  updateHeight(node);
  int balance = height(node->left) - height(node->right);
  if (balance < -1 || balance > 1)
  {
    if (balance > 1 && (strcmp(key, node->left->key) < 0))
      return rightRotate(node);
    if (balance < -1 && (strcmp(key, node->right->key) > 0))
      return leftRotate(node);
    if (balance > 1 && (strcmp(key, node->left->key) > 0))
    {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
    if (balance < -1 && (strcmp(key, node->right->key) < 0))
    {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }
  return node;
}

/* Fonction pour eviter la duplication de code de recherche dans
  l'arbre avl. Renvoyant le noeud qui a la cle key
*/
struct Node* searchNode(struct Node *node, const char *key)
{
  if (!node)
    return NULL;
  if (strcmp(key, node->key) < 0)
    return searchNode(node->left, key);
  else if (strcmp(key, node->key) > 0)
    return searchNode(node->right, key);
  else if (strcmp(key, node->key) == 0)
    return node;
  return node;
}

/* Fonction renvoyant la hauteur de la cle key dans le sous-arbre node.
   NB : Renvoie 0 si la cle n'a pas ete trouvee
*/
int getKeyHeight(struct Node* node, const char *key)
{
  struct Node* new_node = searchNode(node, key);
  if (new_node)
    return new_node->height;
  return 0;
}

/* Fonction renvoyant le rang de la cle key dans le sous-arbre node.
   Par exemple :
     - Renvoie 0 si le noeud de la cle key est le noeud le plus en bas
       à gauche de l'arbre
     - Renvoie le nombre de noeuds dans l'arbre - 1 si le noeud de la cle
       key est le noeud le plus en bas à droite de l'arbre
   NB : Renvoie -1 si la cle n'a pas ete trouvee
*/
int getKeyRank(const struct Node* node, const char *key)
{
  int rank = 0;
  while (node)
  {
    if (strcmp(key, node->key) < 0)
      node = node->left;
    else if (strcmp(key, node->key) > 0)
    {
      rank += nbNode(node->left) + 1;
      node = node->right;
    }
    else
      return nbNode(node->left) + rank;
  }
  return -1;
}

/* Fonction renvoyant la valeur associee a une cle
   (et NULL si la cle n'est pas trouvee)
*/
char *getValue(struct Node *node, const char *key)
{
  struct Node* new_node = searchNode(node, key);
  if (new_node)
    return new_node->value;
  return NULL;
}
