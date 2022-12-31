#include "log.h"
#include "debug.h"

#include "fs.h"

//TODO: Tests
std::deque<fs_entry> FS::search(const std::string& search, bool matchCase, bool exact){
    FUN();
    DEBUG_EX("FS::search()");

    std::deque<fs_entry> ret;
    SQL_res res_names;

    {   //Search the names and note any matches

        std::string sql;
        if(matchCase)
            sql += "PRAGMA case_sensitive_like=ON;";
        else
            sql += "PRAGMA case_sensitive_like=OFF;";

        if (exact)
            sql += "SELECT id, name FROM names WHERE name LIKE ('" + search + "');";
        else
            sql += "SELECT id, name FROM names WHERE name LIKE ('%" + search + "%');";

        res_names = _sql.exec(sql);

        if (res_names.code){
            LOGUE("[SQL Error] '" + _sql.getError() + "' when searching " +
                (exact ? "EXACTLY " : "") +
                (matchCase ? "CASE MATCHED " : "") +
                "for " + search
                );
        }
    }

    {
        //Go through every matched name
        for (std::deque<std::string> name : res_names.result){
            std::string nameId = name.at(0);
            std::string nameStr = name.at(1);

            std::string cmd = "SELECT isDir, id, nameID, parentID FROM entries WHERE nameID = " + nameId + ";";
            SQL_res res = _sql.exec(cmd);

            if (res.code){
                LOGUE("[SQL Error] '" + _sql.getError() + "' when looking up nameID " + nameId);
            }

            for (std::deque<std::string> entry : res.result){
                ret.push_back(fs_entry_parse(entry.at(0), entry.at(1), nameStr, entry.at(2), entry.at(3)));
            }
        }

    }

    return ret;
}
