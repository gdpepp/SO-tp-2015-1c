/*
 * mongodb.c
 *
 *  Created on: 09/06/2015
 *      Author: ezeyuske
 */

#include "mongodb.h"

//mongoc_client_t* client;
//mongoc_collection_t* collection;

void iniciar_mongo(void){
    mongoc_client_t *client;
    mongoc_collection_t *collection;
    mongoc_cursor_t *cursor;
    const bson_t *doc;
    bson_t *query;
    char *str;

	mongoc_init();
	client = mongoc_client_new("mongodb://localhost:27017/");
	collection = mongoc_client_get_collection (client, "test", "restaurants");

	//query = bson_new ();
	query = BCON_NEW("$eq", "{", "building", BCON_UTF8("1007"), "}");
	cursor = mongoc_collection_find (collection, MONGOC_QUERY_NONE, 0, 0, 0, query, NULL, NULL);

	while (mongoc_cursor_next (cursor, &doc)) {
		str = bson_as_json (doc, NULL);
		printf ("%s\n", str);
		bson_free (str);
	}

	bson_destroy (query);
	mongoc_cursor_destroy (cursor);
	mongoc_collection_destroy (collection);
	mongoc_client_destroy (client);
}
