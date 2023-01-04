#include "log.h"
#include "debug.h"

#include "fs.h"

#include <map>

//TODO: Tests
std::deque<fs_entry> FS::search(const std::string& search, bool matchCase, bool exact){
    FUN();
    DEBUG_EX("FS::search()");

    std::deque<fs_entry> ret;
    std::string cmd;

    //Check for matching case
    if(matchCase)
        cmd += "PRAGMA case_sensitive_like=ON;";
    else
        cmd += "PRAGMA case_sensitive_like=OFF;";

    //Construct the core command
    cmd += "SELECT m.name, e.isDir, e.id, e.nameID, e.parentID ";
    cmd += "FROM entries e, names m ";
    cmd += "WHERE e.nameID = m.id AND ";

    //And check if searching exactly
    if (exact)
        cmd += "m.name LIKE ('" + search + "');";
    else
        cmd += "m.name LIKE ('%" + search + "%');";

    //Execute the command    
    SQL_res res = _sql.exec(cmd);

    //Check the return code
    if (res.code){
        LOGUE("[SQL Error] '" + _sql.getError() + "' when searching " +
            (exact ? "EXACTLY " : "") +
            (matchCase ? "CASE MATCHED " : "") +
            "for " + search
            );
        return ret;
    }

    //Transform the results
    for (std::deque<std::string> entry : res.result){
        ret.push_back(fs_entry_parse(entry.at(1), entry.at(2), entry.at(0), entry.at(3), entry.at(4)));
    }

    return ret;
}

std::deque<std::shared_ptr<FSDir>> FS::searchTree(const std::string& search, bool matchCase, bool exact){
    FUN();
    DEBUG_EX("FS::searchTree()");

    std::deque<std::shared_ptr<FSDir>> ret;
    std::string cmd;

    //Check for matching case
    if(matchCase)
        cmd += "PRAGMA case_sensitive_like=ON;";
    else
        cmd += "PRAGMA case_sensitive_like=OFF;";

    cmd += "WITH parent AS(";
    cmd += " SELECT *";
    cmd += " FROM entries WHERE id IN( SELECT id FROM names WHERE name LIKE";

    //And check if searching exactly
    if (exact)
        cmd += " '" + search + "')";
    else
        cmd += " '%" + search + "%')";

    cmd += " UNION ALL";
    cmd += " SELECT entries.*";
    cmd += " FROM entries JOIN parent ON entries.id = parent.parentID)";
    cmd += " SELECT DISTINCT p.id, p.nameID, p.parentID, p.isDir, n.name";
    cmd += " FROM parent p, names n WHERE p.nameID = n.id ORDER BY p.parentID;";

    //Execute the command
    SQL_res res = _sql.exec(cmd);

    //Check the return code
    if (res.code){
        LOGUE("[SQL Error] '" + _sql.getError() + "' when searching " +
            (exact ? "EXACTLY " : "") +
            (matchCase ? "CASE MATCHED " : "") +
            "for " + search
            );
        return ret;
    }

    {//Parse the results into a filesystem tree
        //This map is for caching
        std::map<uint64_t, FSDir*> dirs;

        FSEntry* nEntry;
        for (std::deque<std::string> entry : res.result){
            //Construct the new FSEntry
            nEntry = new FSEntry(nullptr, entry.at(3), entry.at(0), entry.at(4), entry.at(1), entry.at(2));

            //If this is a directory
            if (nEntry->isDir){
                FSDir* nDir = new FSDir(nEntry);
                //We can now delete nEntry and replace it with nDir
                delete nEntry;
                nEntry = nDir;

                //Add the directory to the dirs
                dirs[nEntry->id] = nDir;

                //If this is a root, add it to the roots
                if (nEntry->parentID == 0){
                    ret.push_back(std::shared_ptr<FSDir>{nDir});
                    continue;
                }
            }

            //Add it to its parent
            LOGD("Adding '" + nEntry->name + "' to '" + dirs[nEntry->parentID]->name);
            nEntry->parent = dirs[nEntry->parentID];
            dirs[nEntry->parentID]->children.push_back(std::shared_ptr<FSEntry>{nEntry});
        }
    }

    return ret;
}
