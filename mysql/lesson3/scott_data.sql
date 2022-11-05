create DATABASE scott;

create table dept(
    deptno      int unsigned auto_increment primary key COMMENT '部门编号',
    dname       varchar(15) COMMENT '部门名称',
    loc         varchar(50) COMMENT '部门所在位置'
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='部门表';
 

create table emp(
    empno           int unsigned auto_increment primary key COMMENT '雇员编号',
    ename           varchar(15) COMMENT '雇员姓名',
    job             varchar(10) COMMENT '雇员职位',
    mgr             int unsigned COMMENT '雇员对应的领导的编号',
    hiredate        date COMMENT '雇员的雇佣日期',
    sal             decimal(7,2) COMMENT '雇员的基本工资',
    comm            decimal(7,2) COMMENT '奖金',
    deptno          int unsigned COMMENT '所在部门',
    foreign key(deptno) references dept(deptno)
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='雇员表';
 
 

create table salgrade(
    grade       int unsigned COMMENT '工资等级',
    losal       int unsigned COMMENT '此等级的最低工资',
    hisal       int unsigned COMMENT '此等级的最高工资'  
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='工资等级表';
 

create table bonus(
    ename       varchar(10) COMMENT '雇员姓名',
    job         varchar(9) COMMENT '雇员职位',
    sal         decimal(7,2) COMMENT '雇员工资',
    comm        decimal(7,2) COMMENT '雇员资金'  
)ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='工资表';
 
 

INSERT INTO dept VALUES (10,'ACCOUNTING','NEW YORK');
INSERT INTO dept VALUES (20,'RESEARCH','DALLAS');
INSERT INTO dept VALUES (30,'SALES','CHICAGO');
INSERT INTO dept VALUES (40,'OPERATIONS','BOSTON');
 

INSERT INTO emp VALUES    (7369,'SMITH','CLERK',7902,'1980-12-17',800,NULL,20);
INSERT INTO emp VALUES    (7499,'ALLEN','SALESMAN',7698,'1981-2-20',1600,300,30);
INSERT INTO emp VALUES    (7521,'WARD','SALESMAN',7698,'1981-2-22',1250,500,30);
INSERT INTO emp VALUES    (7566,'JONES','MANAGER',7839,'1981-4-2',2975,NULL,20);
INSERT INTO emp VALUES    (7654,'MARTIN','SALESMAN',7698,'1981-9-28',1250,1400,30);
INSERT INTO emp VALUES    (7698,'BLAKE','MANAGER',7839,'1981-5-1',2850,NULL,30);
INSERT INTO emp VALUES    (7782,'CLARK','MANAGER',7839,'1981-6-9',2450,NULL,10);
INSERT INTO emp VALUES    (7788,'SCOTT','ANALYST',7566,'87-7-13',3000,NULL,20);
INSERT INTO emp VALUES    (7839,'KING','PRESIDENT',NULL,'1981-11-17',5000,NULL,10);
INSERT INTO emp VALUES    (7844,'TURNER','SALESMAN',7698,'1981-9-8',1500,0,30);
INSERT INTO emp VALUES    (7876,'ADAMS','CLERK',7788,'87-7-13',1100,NULL,20);
INSERT INTO emp VALUES    (7900,'JAMES','CLERK',7698,'1981-12-3',950,NULL,30);
INSERT INTO emp VALUES    (7902,'FORD','ANALYST',7566,'1981-12-3',3000,NULL,20);
INSERT INTO emp VALUES    (7934,'MILLER','CLERK',7782,'1982-1-23',1300,NULL,10);
 

INSERT INTO salgrade VALUES (1,700,1200);
INSERT INTO salgrade VALUES (2,1201,1400);
INSERT INTO salgrade VALUES (3,1401,2000);
INSERT INTO salgrade VALUES (4,2001,3000);
INSERT INTO salgrade VALUES (5,3001,9999);
