#include "text.h"

const char errorMsg[][50] = {
    "Error Unknown",
    "Yet Another Error"
};


const char labels[NBOfLabels][100] = {
    "-- Menu Principal --",
    "1) Rechercher un article",
    "2) Afficher le panier",
    "3) Afficher l'historique des operations",
    "4) Quitter",
    "-- Catalogue --",
    ">> Veuillez selectionner une categorie : ",
    ">> Veuillez selectionner une sous categorie : ",
    ">> Veuillez selectionner un item a acheter: ",
    "Voici les articles actuellement en stock :",
    "-- Panier --",
    "-- Checkout --",
    ">> Appuyez sur une touche pour revenir au menu principal : ",
    "Impossible, votre panier dépasse la valeur maximale autorise",
    "1) Modifier un article",
    "2) Passer au paiement",
    "3) Retourner au menu principal",
    "Il n'y a aucun article dans votre panier",
    ">> Veuillez selectionner l'article a modifier : ",
    "Article introuvable",
    "Impossible, pas assez d'articles en stock",
    "Le total de votre panier est : ",
    "Facture par : ",
    "Facture a : ",
    "Facture le : ",
    "Nous vous remercions pour votre achat",
    "Facture N°",
    "- %s ajouté au panier\n",
    "- %s suprimé du panier\n",
    "- Quantité de %s modifié a %s\n",
    "Historique vide",
    ">> Veuillez selectionner la transaction a effectuer : "
};