#include <QObject>
typedef struct fvd_config{

}fvd_config_t;
typedef struct pd_config{
    int w;
    int h;
    int x;
    int y;
}pd_config_t;
typedef struct alg_config{
    QString selected_alg;
    pd_config_t pd;
    fvd_config_t fvd;
}alg_config_t;
