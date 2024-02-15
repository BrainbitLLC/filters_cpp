#ifndef FILTERS_EXPORT_H
#define FILTERS_EXPORT_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "lib_export.h"

#include "f_types.h"

	typedef struct _TFilterList TFilterList;
	typedef struct _TFilter TFilter;


	SDK_SHARED TFilterList* create_TFilterList(TOpStatus*);
	SDK_SHARED void TFilterList_AddFilter(TFilterList*, TFilter*, TOpStatus*);
	SDK_SHARED double TFilterList_Filter(TFilterList*, double, TOpStatus*);
	SDK_SHARED void TFilterList_Filter_array(TFilterList*, double*, int, TOpStatus*);
	SDK_SHARED void TFilter_List_ClearFilters(TFilterList*, TOpStatus*);
	SDK_SHARED void TFilterList_Reset(TFilterList*, TOpStatus*);
	SDK_SHARED void TFilterList_Delete_TFilter(TFilterList*, TFilterID, TOpStatus*);
	SDK_SHARED void delete_TFilterList(TFilterList*, TOpStatus*);

	SDK_SHARED TFilter* create_TFilter_by_param(FilterParam, TOpStatus*);
	SDK_SHARED TFilter* create_custom_TFilter(char*, TOpStatus*);

	SDK_SHARED void TFilter_Reset(TFilter*, TOpStatus*);
	SDK_SHARED void TFilter_ClearParams(TFilter*, TOpStatus*);
	SDK_SHARED void TFilter_SetParams(TFilter*, char*, TOpStatus*);
	SDK_SHARED double TFilter_Filter(TFilter*, double, TOpStatus*);
	SDK_SHARED void TFilter_Filter_array(TFilter*, double*, int, TOpStatus*);
	SDK_SHARED TFilterID getID_TFilter(TFilter*, TOpStatus*);
	SDK_SHARED void delete_TFilter(TFilter*, TOpStatus*);

	SDK_SHARED void get_preinstalled_filter_count(int*, TOpStatus*);
	SDK_SHARED void get_preinstalled_filter_list(FilterParam*, TOpStatus*);

#ifdef __cplusplus
}
#endif

#endif
