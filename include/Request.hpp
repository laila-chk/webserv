/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamer <maamer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:11:54 by mtellami          #+#    #+#             */
/*   Updated: 2023/08/12 19:12:53 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "include.hpp"

class Request {
    private:
        std::map<std::string, std::string>  _req_header;
        std::vector<std::string>            _start_line;
        std::string       _query;
        std::string       _recv_buffer;
        size_t            _buffer_size;
        char              _buffer[SIZE];
        int               _i;
        bool              _bad_request;
        bool              _payload_too_large;
        bool              _method_not_allowed;
        bool              _not_found;
        int               _body_size;
        std::string       _filename;
        bool              _recv_header;

    public:
        Request();
        ~Request();
        int      get_body_size();
        std::string get_protocol(void);
        std::string get_query();
        std::string getContentType();
        std::string getContentLength();
        void    get_request_header(SOCK_FD & _socket, bool & _done_recv);
        void    parse_request_header(bool & _done_recv);

        void    get_request_body(SOCK_FD & _socket, bool & _done_recv, std::string path);
        void    write_body_chunk(bool & _done_recv, std::string path);

        std::string get_method(void);
        std::string get_url(void);
        std::map<std::string, std::string> get_req_header(void);
        bool        recieve_header(void);
        bool        is_bad_request(void);
        bool        is_payload_too_large(void);
        bool        is_not_found(void);
        void        method_is_not_allowed(bool stat);
        void        payload_is_too_large(bool stat);
				void				transfer_encoding(SOCK_FD & _socket, bool & _done_recv, std::string path);

};

        std::string rand_name(void);
#endif
