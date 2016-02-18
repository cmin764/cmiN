create or replace view emp_1500 as
  select * from emp
  where sal >= 1500
  order by ename;
  
select * from emp_1500
/


create or replace view show_info as
  select owner, object_type, object_name
  from all_objects
  where owner = user
  order by object_type;

select * from show_info;
/