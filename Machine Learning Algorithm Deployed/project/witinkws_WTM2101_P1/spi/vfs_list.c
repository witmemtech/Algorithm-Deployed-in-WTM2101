#ifdef CONFIG_RAM_KWS_SPI

#include "vfs_list.h"
#include "wtm2101.h"

#ifndef NULL
#define NULL 0
#endif

#ifndef  LIST_ENTER_CRITICAL
#define  LIST_ENTER_CRITICAL()    __disable_irq()
#endif

#ifndef LIST_EXIT_CRITICAL
#define LIST_EXIT_CRITICAL()      __enable_irq()
#endif

extern void *pvPortMalloc( size_t xWantedSize );
extern void vPortFree( void *pv );
#ifndef LIST_MALLOC
#define LIST_MALLOC(size)  pvPortMalloc(size)
#endif

#ifndef LIST_FREE
#define LIST_FREE(point)   vPortFree(point)
#endif

#ifndef __VFS_CORE__
#define __vfs_core_strtok(n,v)  NULL   
#endif

#define VFS_LIST_MAX_SIZE  (10 * 1024)

//************************************
// Method:    vfs_list_head
// FullName:  vfs_list_head
// Access:    public 
// Returns:   vfs_list_type *
// Qualifier: ����һ���µ�listͷ�ڵ�
//************************************
vfs_list_type * vfs_list_head()
{
    vfs_list_type * head = (vfs_list_type *)LIST_MALLOC(sizeof(vfs_list_type));
    if (head == NULL)
        return NULL;
    head->data = NULL;
    head->count = 0x00;
    head->next = NULL;
    return head;
}
//************************************
// Method:    vfs_list_del
// FullName:  vfs_list_del
// Access:    public 
// Returns:   int
// Qualifier: �ͷ�listȫ���ڵ㼰�����ݣ����ͷ�listͷ�ڵ��ڴ�
// Parameter: vfs_list_type * _list
//************************************
int vfs_list_del(vfs_list_type *_list)
{
    if (_list == NULL)return 0x00;
    vfs_list_clear(_list);
    LIST_FREE(_list);
    return 1;
}
//************************************
// Method:    vfs_list_del_safe
// FullName:  vfs_list_del_safe
// Access:    public 
// Returns:   int
// Qualifier: �̰߳�ȫ�汾vfs_list_del
// Parameter: vfs_list_type * _list
//************************************
int vfs_list_del_safe(vfs_list_type *_list)
{
    if (_list == NULL)return 0x00;
    vfs_list_clear_safe(_list);
    LIST_FREE(_list);
    return 1;
}
//************************************
// Method:    vfs_list_remove
// FullName:  vfs_list_remove
// Access:    public 
// Returns:   int
// Qualifier: ɾ��ָ���ڵ㼰�估�����ݣ�index������0��ʼ��
// Parameter: vfs_list_type * _list
// Parameter: uint index
//************************************
int vfs_list_remove(vfs_list_type *_list, uint index)
{
    vfs_list_type * node = NULL, *father = NULL;
    if (_list == NULL)
        return -1;
    if (_list->count <= index)
    {
        return -2;                                                          //Խ��
    }
    node = _list->next;
    father = _list;
    while (index > 0x00 && node != NULL)
    {
        index -= 0x01;
        father = node;
        node = node->next;
    }
    father->next = node->next;
    _list->count -= 0x01;
    /************************************************************************

    �ͷŽڵ��ڴ�ͽڵ�ָ�����ݵ��ڴ棬�������

    ************************************************************************/

    if (node->data)LIST_FREE(node->data);
    LIST_FREE(node);
    return 0x01;
}
//************************************
// Method:    vfs_list_remove_safe
// FullName:  vfs_list_remove_safe
// Access:    public 
// Returns:   int
// Qualifier: �̰߳�ȫ��vfs_list_remove
// Parameter: vfs_list_type * _list
// Parameter: uint index
//************************************
int vfs_list_remove_safe(vfs_list_type *_list, uint index)
{
    int re = -1;
    LIST_ENTER_CRITICAL();
    re = vfs_list_remove(_list, index);
    LIST_EXIT_CRITICAL();
    return re;
}
//************************************
// Method:    vfs_list_clear
// FullName:  vfs_list_clear
// Access:    public 
// Returns:   int
// Qualifier: ���listȫ���ڵ㼰��Ԫ��
// Parameter: vfs_list_type * _list
//************************************
int vfs_list_clear(vfs_list_type *_list)
{
    vfs_list_type * node = NULL;
    if (_list == NULL)
        return 0;
    if (_list->count == 0x00)
    {
        _list->next = NULL;
        return 1;
    }
    while (_list->next != NULL)
    {
        node = _list->next;
        _list->next = node->next;
        if (node->data)
            LIST_FREE(node->data);
        LIST_FREE(node);
    }
    _list->count = 0x00;
    return 1;
}
//************************************
// Method:    vfs_list_clear_safe
// FullName:  vfs_list_clear_safe
// Access:    public 
// Returns:   int
// Qualifier: �̰߳�ȫ��vfs_list_clear
// Parameter: vfs_list_type * _list
//************************************
int vfs_list_clear_safe(vfs_list_type *_list)
{
    vfs_list_type * node = NULL;
    if (_list == NULL)
        return 0;
    LIST_ENTER_CRITICAL();
    if (_list->count == 0x00)
    {
        LIST_EXIT_CRITICAL();
        _list->next = NULL;
        return 1;
    }
    while (_list->next != NULL)
    {
        node = _list->next;
        _list->next = node->next;
        if (node->data)
            LIST_FREE(node->data);
        LIST_FREE(node);
    }
    _list->count = 0x00;
    LIST_EXIT_CRITICAL();
    return 1;
}
//************************************
// Method:    vfs_list_push
// FullName:  vfs_list_push
// Access:    public 
// Returns:   int
// Qualifier: �����ݼ���listβ��
// Parameter: vfs_list_type * _list
// Parameter: unsigned char * data
// Parameter: unsigned int count
//************************************
int vfs_list_push(vfs_list_type *_list, unsigned char * data, unsigned int count)
{
    vfs_list_type *node = NULL;
    vfs_list_type *add_node = NULL;
    if (_list == NULL)
        return 0;
    if (_list->count != 0x00)
    {
        node = _list->next;
        while (node->next != NULL)
        {
            node = node->next;
        }
    }
    else
        node = _list;
    add_node = (vfs_list_type *)LIST_MALLOC(sizeof(vfs_list_type));
    if (add_node == NULL)
    {
        return (char)-1;

    }add_node->next = NULL;
    add_node->count = count;
    add_node->data = data;
    _list->count += 0x01;
    if (node == NULL)//���п�
        _list->next = add_node;
    else
        node->next = add_node;
    return 1;

}
//************************************
// Method:    vfs_list_push_safe
// FullName:  vfs_list_push_safe
// Access:    public 
// Returns:   int
// Qualifier: �̰߳�ȫ��vfs_list_push
// Parameter: vfs_list_type * _list
// Parameter: unsigned char * data
// Parameter: unsigned int count
//************************************
int vfs_list_push_safe(vfs_list_type *_list, unsigned char * data, unsigned int count)
{
    vfs_list_type *node = NULL;
    vfs_list_type *add_node = NULL;
    add_node = (vfs_list_type *)LIST_MALLOC(sizeof(vfs_list_type));
    if (add_node == NULL)
    {
        return -1;
    }
    LIST_ENTER_CRITICAL();
    if (_list == NULL)
    {
        LIST_EXIT_CRITICAL();
        LIST_FREE(add_node);
        return -2;
    }
    if (_list->count != 0x00)
    {
        node = _list->next;
        while (node->next != NULL)
        {
            node = node->next;
        }
    }
    else
        node = _list;
    add_node->next = NULL;
    add_node->count = count;
    add_node->data = data;
    _list->count += 0x01;
    node->next = add_node;
    LIST_EXIT_CRITICAL();
    return 1;

}
//************************************
// Method:    vfs_list_push_for_data
// FullName:  vfs_list_push_for_data
// Access:    public 
// Returns:   int
// Qualifier: ��data�����offsetƫ�ƴ���ȡlen���ȵ����ݼ��뵽listβ��
// Parameter: vfs_list_type * _list
// Parameter: unsigned char * data
// Parameter: unsigned int offset
// Parameter: unsigned int len
//************************************
int vfs_list_push_for_data(vfs_list_type *_list, unsigned char *data, unsigned int offset, unsigned int len)
{
    uchar *item = NULL;
    if (_list == NULL || data == NULL || len > VFS_LIST_MAX_SIZE)return -1;

    item = LIST_MALLOC(len);
    if (item == NULL)return -2;
    memcpy(item, data + offset, len);
    if (vfs_list_push(_list, item, len) < 0x00)
    {
        LIST_FREE(item); return -3;
    }
    return 0x01;
}
//************************************
// Method:    vfs_list_push_for_data_safe
// FullName:  vfs_list_push_for_data_safe
// Access:    public 
// Returns:   int
// Qualifier: �̰߳�ȫ��vfs_list_push_for_data
// Parameter: vfs_list_type * _list
// Parameter: unsigned char * data
// Parameter: unsigned int offset
// Parameter: unsigned int len
//************************************
int vfs_list_push_for_data_safe(vfs_list_type *_list, unsigned char *data, unsigned int offset, unsigned int len)
{
    uchar *item = NULL;
    if (_list == NULL || data == NULL || len > VFS_LIST_MAX_SIZE)return -1;
    item = LIST_MALLOC(len);//��Ϊʹ�ô˺����Ĵ�����ַ���ת�棬������Ҫ��β����
    if (item == NULL)return -2;
    memcpy(item, data + offset, len);
    if (vfs_list_push_safe(_list, item, len) < 0x00)
    {
        LIST_FREE(item); return -3;
    }
    return 0x01;
}
//************************************
// Method:    vfs_list_insert
// FullName:  vfs_list_insert
// Access:    public 
// Returns:   int
// Qualifier: �����ݼ��뵽list��ָ������Ϊindex��������index��0��ʼ
// Parameter: vfs_list_type * _list
// Parameter: uint index
// Parameter: unsigned char * data
// Parameter: unsigned int len
//************************************
int vfs_list_insert(vfs_list_type *_list, uint index, unsigned char * data, unsigned int len)
{
    vfs_list_type *temp = NULL, *father = NULL, *item = NULL;
    if (_list == NULL || data == NULL || len == 0x00)return -1;
    if (index >= _list->count)
    {
        return vfs_list_push(_list, data, len);
    }
    father = _list;
    temp = father->next;
    while (index-- > 0x00)
    {
        father = _list;
        temp = father->next;
    }
    if (father == NULL)
        return -2;
    item = LIST_MALLOC(sizeof(vfs_list_type));
    if (item == NULL)return -3;
    item->data = LIST_MALLOC(len);
    if (item->data == NULL)
    {
        LIST_FREE(item); return -4;
    }
    memcpy(item->data, data, len);
    item->count = len;
    father->next = item;
    item->next = temp;
    _list->count++;

    return 0x01;
}
//************************************
// Method:    vfs_list_insert_safe
// FullName:  vfs_list_insert_safe
// Access:    public 
// Returns:   int
// Qualifier: �̰߳�ȫ��vfs_list_insert
// Parameter: vfs_list_type * _list
// Parameter: uint index
// Parameter: unsigned char * data
// Parameter: unsigned int len
//************************************
int vfs_list_insert_safe(vfs_list_type *_list, uint index, unsigned char * data, unsigned int len)
{

    vfs_list_type *temp = NULL, *father = NULL, *item = NULL;
    if (_list == NULL || data == NULL || len == 0x00)return -1;
    LIST_ENTER_CRITICAL();
    if (index >= _list->count)
    {
        LIST_EXIT_CRITICAL();
        return vfs_list_push_safe(_list, data, len);
    }
    father = _list;
    temp = father->next;
    while (index-- > 0x00)
    {
        father = _list;
        temp = father->next;
    }
    if (father == NULL) { LIST_EXIT_CRITICAL(); return -2; }
    item = LIST_MALLOC(sizeof(vfs_list_type));
    if (item == NULL) { LIST_EXIT_CRITICAL(); return -3; }
    item->data = LIST_MALLOC(len);
    if (item->data == NULL) { LIST_EXIT_CRITICAL(); LIST_FREE(item); return -4; }
    memcpy(item->data, data, len);
    item->count = len;
    father->next = item;
    item->next = temp;
    _list->count++;
    LIST_EXIT_CRITICAL();
    return 0x01;
}
//************************************
// Method:    vfs_list_pop
// FullName:  vfs_list_pop
// Access:    public 
// Returns:   vfs_list_type
// Qualifier: ��list�ײ�Ԫ���Ƴ���list��ע�⣬vfs_list_type.data���ڴ沢û���ͷţ���Ҫ�û��Լ��ͷţ����������ڴ�й©
// Parameter: vfs_list_type * _list
//************************************
vfs_list_type vfs_list_pop(vfs_list_type *_list)
{
    vfs_list_type re = { NULL,0X00,NULL };
    vfs_list_type * node = NULL;
    if (_list == NULL)
        return re;
    if (_list->count == 0x00 || _list->next == NULL)
    {
        return re;
    }
    node = _list->next;
    _list->next = node->next;
    _list->count -= 0x01;
    re.count = node->count;
    re.data = node->data;
    re.next = NULL;
    //ע�⣬�˴���û���ͷ����ݵ��ڴ棬�������ⲿ��ʽ���ͷ�re.data���ڴ�.
    LIST_FREE(node);
    return re;
}
//************************************
// Method:    vfs_list_pop_safe
// FullName:  vfs_list_pop_safe
// Access:    public 
// Returns:   vfs_list_type
// Qualifier: �̰߳�ȫ��vfs_list_pop
// Parameter: vfs_list_type * _list
//************************************
vfs_list_type vfs_list_pop_safe(vfs_list_type *_list)
{
    vfs_list_type re = { NULL,0X00,NULL };
    vfs_list_type * node = NULL;
    if (_list == NULL)
        return re;
    LIST_ENTER_CRITICAL();
    if (_list->count == 0x00 || _list->next == NULL)
    {
        LIST_EXIT_CRITICAL();
        return re;
    }
    node = _list->next;
    _list->next = node->next;
    _list->count -= 0x01;
    re.count = node->count;
    re.data = node->data;
    re.next = NULL;
    //ע�⣬�˴���û���ͷ����ݵ��ڴ棬�������ⲿ��ʽ���ͷ�re.data���ڴ�.
    LIST_EXIT_CRITICAL();
    LIST_FREE(node);
    return re;
}
//************************************
// Method:    vfs_list_find_at
// FullName:  vfs_list_find_at
// Access:    public 
// Returns:   vfs_list_type *
// Qualifier: ��ȡָ������index���Ľڵ㣬index��0��ʼ
// Parameter: vfs_list_type * _list
// Parameter: int index
//************************************
vfs_list_type * vfs_list_find_at(vfs_list_type *_list, int index)
{
    vfs_list_type * node = NULL;
    if (_list == NULL)
        return NULL;
    if (_list->count <= index || _list->next == NULL || index < 0)
    {
        return NULL;
    }
    node = _list->next;
    while (index > 0x00)
    {
        index -= 0x01;
        node = node->next;
    }
    return node;
}
//************************************
// Method:    vfs_list_find_at_safe
// FullName:  vfs_list_find_at_safe
// Access:    public 
// Returns:   vfs_list_type *
// Qualifier: �̰߳�ȫ��vfs_list_find_at
// Parameter: vfs_list_type * _list
// Parameter: int index
//************************************
vfs_list_type * vfs_list_find_at_safe(vfs_list_type *_list, int index)
{
    vfs_list_type * node = NULL;
    if (_list == NULL)
        return NULL;
    LIST_ENTER_CRITICAL();
    if (_list->count <= index || _list->next == NULL || index < 0)
    {
        LIST_EXIT_CRITICAL();
        return NULL;
    }
    node = _list->next;
    while (index > 0x00)
    {
        index -= 0x01;
        node = node->next;
    }
    LIST_EXIT_CRITICAL();
    return node;
}
//************************************
// Method:    vfs_list_create_for_str
// FullName:  vfs_list_create_for_str
// Access:    public 
// Returns:   vfs_list_type *
// Qualifier: ���ַ���data�ң���divsionΪ�ָ������ָ������list
// Parameter: const char * data
// Parameter: const char divsion
//************************************
//vfs_list_type * vfs_list_create_for_str(const char * data, const char divsion)
//{
//    AD_ERR_ASSERT_START();

//    uint index = 0x00, start = 0x00;
//    uchar split_flag = 0;
//    uchar div[2] = { divsion,0 };
//    vfs_list_type *parms = __vfs_core_strtok_r(data, div);
//    AD_ERR_ASSERT(parms, -1);
//    AD_ERR_ASSERT(data, -2);

//    AD_ERR_ASSERT(0, parms);

//    AD_ERR_ASSERT_END();
//    if (__ad__err_code__ < 0x00)
//    {
//        if (parms)vfs_list_del(parms);
//        __ad__err_code__ = 0x00;
//    }
//    AD_ERR_ASSERT_RETURN(vfs_list_type *);
//}
//************************************
// Method:    vfs_list_secede
// FullName:  vfs_list_secede
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: vfs_list_type * _list
// Parameter: uint index
//************************************
int vfs_list_secede(vfs_list_type *_list, uint index)
{
    vfs_list_type * node = NULL, *father = NULL;
    if (_list == NULL)
        return -1;
    if (_list->count <= index)
    {
        return -2;//Խ��
    }
    node = _list->next;
    father = _list;
    while (index > 0x00 && node != NULL)
    {
        index -= 0x01;
        father = node;
        node = node->next;
    }
    father->next = node->next;
    _list->count -= 0x01;

    //ע�⣬�˴����ͷž�������ݣ�ֻ�ǽ����ݴ�list����
    LIST_FREE(node);
    return 0x01;
}

int vfs_list_secede_safe(vfs_list_type *_list, uint index)
{
    vfs_list_type * node = NULL, *father = NULL;
    if (_list == NULL)
        return -1;
    LIST_ENTER_CRITICAL();
    if (_list->count <= index)
    {
        LIST_EXIT_CRITICAL();
        return -2;//Խ��
    }
    node = _list->next;
    father = _list;
    while (index > 0x00 && node != NULL)
    {
        index -= 0x01;
        father = node;
        node = node->next;
    }
    father->next = node->next;
    _list->count -= 0x01;
    LIST_EXIT_CRITICAL();
    //ע�⣬�˴����ͷž�������ݣ�ֻ�ǽ����ݴ�list����
    LIST_FREE(node);
    return index;
}

#endif
