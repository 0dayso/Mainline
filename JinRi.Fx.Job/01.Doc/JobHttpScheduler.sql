USE FxDB
GO
if exists (select 1
            from  sysobjects
           where  id = object_id('JobHttpScheduler')
            and   type = 'U')
   drop table JobHttpScheduler
go

/*==============================================================*/
/* Table: JobHttpScheduler                                      */
/*==============================================================*/
create table JobHttpScheduler (
   JobHttpSchedulerID   int                  identity,
   JobName              varchar(100)         not null,
   GroupName            varchar(100)         not null default 'DefaultGroup',
   RequestURL           varchar(100)         not null,
   RequestType          int                  not null default 0,
   JobDescription       nvarchar(200)        not null default '',
   StartTime            datetime             not null default getdate(),
   TriggerType          int                  not null default 0,
   RepeatCount          int                  not null default -1,
   RepeatInterval       int                  not null default 0,
   CronExpression       varchar(200)         not null,
   JobStatus            int                  not null default 0,
   AddTime              datetime             not null default getdate(),
   constraint PK_JOBHTTPSCHEDULER primary key (JobHttpSchedulerID)
)
go

declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   '�ƻ������',
   'user', @CurrentUser, 'table', 'JobHttpScheduler'
go

declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   '����',
   'user', @CurrentUser, 'table', 'JobHttpScheduler', 'column', 'JobHttpSchedulerID'
go

declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Job���ƣ�����Ψһ',
   'user', @CurrentUser, 'table', 'JobHttpScheduler', 'column', 'JobName'
go

declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   '����',
   'user', @CurrentUser, 'table', 'JobHttpScheduler', 'column', 'GroupName'
go

declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   '�����ַ����ɵ�URL��ַ�����磺http://www.jinri.cn/Example.aspx',
   'user', @CurrentUser, 'table', 'JobHttpScheduler', 'column', 'RequestURL'
go

declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   '����ʼʱ��',
   'user', @CurrentUser, 'table', 'JobHttpScheduler', 'column', 'StartTime'
go

declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Trigger���ͣ�0��SimpleTrigger��1��CronTrigger',
   'user', @CurrentUser, 'table', 'JobHttpScheduler', 'column', 'TriggerType'
go

declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'SimpleTrigger�ظ�ִ�д�����-1��ʾ���޴Σ�������������ʾ�����ظ��Ĵ���',
   'user', @CurrentUser, 'table', 'JobHttpScheduler', 'column', 'RepeatCount'
go

declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'SimpleTrigger�ظ�ִ�м��ʱ�䣬��λ����',
   'user', @CurrentUser, 'table', 'JobHttpScheduler', 'column', 'RepeatInterval'
go

declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   'Cron���ʽ',
   'user', @CurrentUser, 'table', 'JobHttpScheduler', 'column', 'CronExpression'
go

declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   '0:������1����ͣ',
   'user', @CurrentUser, 'table', 'JobHttpScheduler', 'column', 'JobStatus'
go

declare @CurrentUser sysname
select @CurrentUser = user_name()
execute sp_addextendedproperty 'MS_Description', 
   '���ʱ��',
   'user', @CurrentUser, 'table', 'JobHttpScheduler', 'column', 'AddTime'
go
