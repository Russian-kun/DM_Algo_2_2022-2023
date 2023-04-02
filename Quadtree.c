#include "Quadtree.h"

Particle* allouerParticle(double x, double y, double vx, double vy) {
    Particle* p = (Particle*)malloc(sizeof(Particle));
    p->x = x;
    p->y = y;
    p->vx = vx;
    p->vy = vy;
    return p;
}

void libererParticle(Particle* p) {
    free(p);
}

void afficherParticle(Particle* p) {
    printf("Particle: x=%d, y=%d, vx=%d, vy=%d", p->x, p->y, p->vx, p->vy);
}

Cell* alloueCell(Particle* p) {
    Cell* c = (Cell*)malloc(sizeof(Cell));
    c->p = p;
    c->next = NULL;
    return c;
}

void libererCell(Cell* c) {
    free(c);
}

void afficherCell(Cell* c) {
    afficherParticle(c->p);
}

Noeud* allouerNoeud(double x, double y, double w, double h) {
    Noeud* n = (Noeud*)malloc(sizeof(Noeud));
    n->x = x;
    n->y = y;
    n->width = w;
    n->height = h;
    n->nbp = 0;
    n->nw = NULL;
    n->ne = NULL;
    n->sw = NULL;
    n->se = NULL;
    n->plist = NULL;
    return n;
}

void libererNoeud(Noeud* n) {
    if (n->nw != NULL) {
        libererNoeud(n->nw);
        libererNoeud(n->ne);
        libererNoeud(n->sw);
        libererNoeud(n->se);
    } else {
        Cell* c = n->plist;
        while (c != NULL) {
            Cell* tmp = c;
            c = c->next;
            libererCell(tmp);
        }
    }
    free(n);
}

void construireQuadTree(Noeud* n, int k, double xmin, double xmax, double ymin, double ymax) {
    n->nbp = 0;
    n->plist = NULL;
    if (k == 1) {
        return;
    }
    double xmid = (xmin + xmax) / 2.0;
    double ymid = (ymin + ymax) / 2.0;
    n->nw = allouerNoeud(xmin, ymid, xmid - xmin, ymax - ymid);
    n->ne = allouerNoeud(xmid, ymid, xmax - xmid, ymax - ymid);
    n->sw = allouerNoeud(xmin, ymin, xmid - xmin, ymid - ymin);
    n->se = allouerNoeud(xmid, ymin, xmax - xmid, ymid - ymin);
    construireQuadTree(n->nw, k / 2, xmin, xmid, ymid, ymax);
    construireQuadTree(n->ne, k / 2, xmid, xmax, ymid, ymax);
    construireQuadTree(n->sw, k / 2, xmin, xmid, ymin, ymid);
    construireQuadTree(n->se, k / 2, xmid, xmax, ymin, ymid);
}
