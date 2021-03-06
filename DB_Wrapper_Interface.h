/* Distributed under the BSD license (http://opensource.org/licenses/BSD-2-Clause) *
 * Copyright (c) 2012, Rostislav Kuratch                                           *
 * All rights reserved.                                                            */

#pragma once

#include "Mutex.h"


class DB_Wrapper_Interface
{
    public:

        DB_Wrapper_Interface(): val_delim_('='), col_delim_('|'), row_delim_('*') {}
        virtual ~DB_Wrapper_Interface() {}

        virtual std::string connect(const std::string& connection_string) = 0;

        virtual int begin_transaction() = 0;
        virtual std::string commit(const int trans_ptr) = 0;
        virtual std::string rollback(const int trans_ptr) = 0;

        virtual std::string exec(const int trans_ptr, const std::string& query) = 0;
        virtual std::string exec(const std::string& query) = 0;
        virtual std::string disconnect() = 0;
        
        void set_delims(const char val_delim, const char col_delim, const char row_delim)
        {
            Mutex::Scoped_Lock lock(mutex_);
            val_delim_ = val_delim; col_delim_ = col_delim; row_delim_= row_delim;
        }


    protected:

        char val_delim_, col_delim_, row_delim_;
        Mutex mutex_;

        std::string make_err_str(const char* error_desc) { std::string delim(" "); delim[0] = row_delim_; return "error" + delim + error_desc; }
};
