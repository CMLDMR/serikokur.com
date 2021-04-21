#ifndef DIALOG_H
#define DIALOG_H

#include "BaseClass/containerwiget.h"
#include "BaseClass/dbclass.h"

class Dialog : public WDialog , public DBClass , public UserClass
{
public:
    Dialog(mongocxx::database* _db , const bsoncxx::document::value &userValue , const std::string &title = "");


};

#endif // DIALOG_H
