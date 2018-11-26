//
// Created by 杨乐 on 2018/11/26.
//

#ifndef YOURSQL_RM_ERROR_H
#define YOURSQL_RM_ERROR_H

#define RM_BADRECSIZE      (START_RM_WARN + 0)  // rec size invalid <= 0
#define RM_NORECATRID      (START_RM_WARN + 1)  // This rid has no record

#define RM_LASTWARN RM_NORECATRID

#define START_RM_ERR        -1
#define RM_SIZETOOBIG      (START_RM_ERR - 0)  // record size too big
#define RM_PF              (START_RM_ERR - 1)  // error in PF
#define RM_NULLRECORD      (START_RM_ERR - 2)
#define RM_RECSIZEMISMATCH (START_RM_ERR - 3)  // record size mismatch
#define RM_HANDLEOPEN      (START_RM_ERR - 4)
#define RM_FCREATEFAIL     (START_RM_ERR - 5)
#define RM_FNOTOPEN        (START_RM_ERR - 6)
#define RM_BAD_RID         (START_RM_ERR - 7)
#define RM_EOF             (START_RM_ERR - 8)  // end of file
#define RM_BAD_FILESCAN    (START_RM_ERR - 9)  // file scan error

#define RM_LASTERROR RM_BAD_FILESCAN

#endif //YOURSQL_RM_ERROR_H
